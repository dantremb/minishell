/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/25 01:47:02 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char **environ;

/* ******************BUILT-IN************************************************ */

void	ft_echo(char *buffer)
{
	printf("%s\n", buffer);
}

void	ft_env(void)
{
	int	i;

	i = -1;
	while(environ[++i])
		printf("%s\n", environ[i]);

}

/* ********************EXIT************************************************** */

void	ft_exit(t_data *data, char *str, int s)
{
	if (s <= 0)
		ft_putstr_fd(str, 2);
	if (s <= 1)
		free(data->buffer);
	if (s <= 2)
		ft_free_array(environ);
	exit(0);
}

/* **********************INIT ENVIRONEMENT*********************************** */

void	ft_copy_env(t_data *data)
{
	printf("copy environement\n");
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(sizeof(char *), ft_array_size(environ));
	if (tmp == NULL)
		ft_exit(data, "Malloc error\n", 0);
	while (environ[i])
	{
		tmp[i] = ft_strdup(environ[i]);
		if (!tmp[i])
			ft_exit(data, "Malloc error\n", 0);
		i++;
	}
	environ = tmp;
}

void	ft_init_environement(t_data *data)
{
	printf("Init environment\n");
	data->nb_cmd = 0;
	data->buffer = NULL;
	data->prompt = NULL;
	data->cmds = NULL;
	ft_copy_env(data);
}

/* ************************READLINE UTILS************************************ */

char	*ft_get_prompt(void)
{
	char	*prompt;

	prompt = ft_strjoin("\033[0;32m", getenv("USER") , 0);
	prompt = ft_strjoin(prompt, "@", 1);
	prompt = ft_strjoin(prompt, "Minishell", 1);
	prompt = ft_strjoin(prompt, ": ", 1);
	prompt = ft_strjoin(prompt, "\033[0;34m", 1);
	prompt = ft_strjoin(prompt, getenv("PWD"), 1);
	prompt = ft_strjoin(prompt, "> ", 1);
	prompt = ft_strjoin(prompt, "\033[0m", 1);
	return (prompt);
}

bool	ft_is_only_space(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

/* **************************PARSING***************************************** */


/* *******************ENGINE************************************************* */


/* ***********************MAIN*********************************************** */

char	*ft_strtok(char *buffer)
{
	static char	*save;
	char *ret;
	
	if (!save)
		save = buffer;
	ret = save;
	while (save && *save != 32) 
	{
		if (*save == '\0')
		{
			save = NULL;
			return (ret);
		}
		else if (*save == 39 || *save == 34)
		{
			save = strchr(save + 1, *save);
			if (!save)
				return (ret);
			save++;
		}
		else
			save++;	
	}
	if (save)
		*save++ = 0;
	return (ret);
}

void 	ft_parse(char *buffer)
{
	char *token;

	token = ft_strtok(buffer);
	while (token)
	{
		printf("TOK = %s\n", token);
		token = ft_strtok(NULL);
	}
}

int	main(void)
{
	t_data data;

	ft_init_environement(&data);// Copy global environ variable to heap
	while (1)
	{
		data.prompt = ft_get_prompt();// Get user and path for prompt
		data.buffer = readline(data.prompt);// Fill the buffer with user input
		free(data.prompt);// Free the prompt for next iteration
		if (ft_is_only_space(data.buffer))// Newline on empty buffer
			continue ;
		else
		{
			printf("i will parse [%s]\n", data.buffer);
			ft_parse(data.buffer);
		}
		free (data.buffer);// Free buffer for next iteration
	}
}
