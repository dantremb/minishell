/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/29 12:29:51 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#define DBQUOTE 34
#define SQUOTE 39
#define SPACE 32

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

int		*ft_open_file(char *buffer)
{
	int		*fd;

	fd = open(buffer, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(buffer, 2);
		ft_putstr_fd(" not found\n", 2);
		return (NULL);
	}
	return (fd);
}

char	*ft_get_path(char *buffer)
{
	char	*program;
	char	*env_path;
	char	**fcnt_path;
	int		i;

	i = 0;
	if (access(buffer, F_OK | X_OK) == 0)
		return (buffer);
	program = ft_strjoin("/", buffer, 0);
	env_path = getenv("PATH");
	if (env_path == NULL || )
		return (NULL);
	fcnt_path = ft_strsplit(env_path, ':');
	if (fcnt_path == NULL)
		return (NULL);
	while (fcnt_path[i])
	{
		test_path = ft_strjoin([ifcnt_path], program);
		if (access(test_path, F_OK | X_OK) == 0)
			break ;
		free (test_path);
		test_path = NULL;
		i++;
	}
	ft_free_array(fcnt_path);
	free(program);
	return (test_path);
}

char	*ft_strtok(char *buffer)
{
	static char	*save;
	char *ret;
	
	if (!save)
		save = buffer;
	ret = save;
	while (save && *save != SPACE)
	{
		if (*save == '\0')
		{
			save = NULL;
			return (ret);
		}
		else if (*save == DBQUOTE || *save == SQUOTE)
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

int	ft_token_count(t_data *data)
{
	char *token_count;
	
	token_count = ft_strtok(data->buffer);
	while(token_count)
	{
		data->nb_cmd++;
		token_count = ft_strtok(NULL);
	}
	
}

void 	ft_parse(t_data *data)
{
	token = ft_strtok(buffer);
	while (token)
	{
		printf("TOK = %s\n", token);
		token = ft_strtok(NULL);
	}
}

/* *******************ENGINE************************************************* */


/* ***********************MAIN*********************************************** */

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
			ft_color(1);
			printf("i will parse [%s]\n", data.buffer);
			ft_color(7);
			ft_parse(&data);
		}
		free (data.buffer);// Free buffer for next iteration
	}
}

/*
char	*ft_strtok(char *buffer)
{
	static char	*save; //pointer to insert NULL after token and keep the rest of the buffer
	char *ret; //start of the token
	
	if (!save) //if save is NULL, we are at the beginning of the buffer
		save = buffer; //so we make a copy of the pointer to the buffer
	ret = save; //we make a copy of the pointer to the save pointer to keep the start of the token
	while (save && *save != 32) //while we are not on a space character
	{
		if (*save == '\0') // if we are at the end of the buffer
		{
			save = NULL; //set save to NULL for the next call to return NULL directly
			return (ret); //return the pointer to the start of the token that will send all the remaining buffer
		}
		else if (*save == 39 || *save == 34) // if we are on a double or single quotes
		{
			save = strchr(save + 1, *save); // we change our pointer to the next quote with strchr
			if (!save) // if he return Null then its a syntax error
				return (ret); // so we return all the remaining buffer
			save++; // we move the pointer to the next character after the quote to continue the parsing
		}
		else
			save++;	//we go to the next character if it is not a space or a quote
	}
	if (save) // if save is not NULL, we are at the end of the token
		*save++ = 0; //we insert a NULL character to the end of the token and increment the save pointer for the next token
	return (ret); //we return the pointer we copied at the start of the token
}
*/