/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/31 00:23:20 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* ******************BUILT-IN************************************************ */

/* ******************EXIT AND FREE******************************************* */

void ft_free_table(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->cmd_count)
		free(data->cmd[i].token);
	free(data->cmd);
	free(data->buffer);
}

void	ft_exit(t_data *data, char *str, int s)
{
	if (s <= 0)
		ft_putstr_fd(str, 2);
	if (s <= 1)
		free(data->buffer);
	if (s <= 2)
		ft_free_array(data->env);
	exit(0);
}

/* **********************INIT ENVIRONEMENT*********************************** */

void	ft_init_environement(t_data *data, char **env)
{
	int		i;

	data->buffer = NULL;
	data->prompt = NULL;
	data->cmd_count = 0;
	data->cmd = NULL;
	i = 0;
	data->env = ft_calloc(sizeof(char *), ft_array_size(env));
	if (data->env == NULL)
		ft_exit(data, "Malloc Error\n", 0);
	while (env[i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			ft_exit(data, "Malloc Error\n", 0);
		i++;
	}
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

void	ft_print_table(t_data *data)
{
	int i;
	int j;
	
	i = 0;
	while (i < data->cmd_count)
	{
		j = 0;
		while (data->cmd[i].token[j])
		{
			printf("%s\n", data->cmd[i].token[j]);
			j++;
		}
		i++;
	}
}

/* **************************PARSING***************************************** */

char	*ft_trim_space(char *buffer)
{
	int		i;
	
	if (!buffer)
		return (buffer);
	i = ft_strlen(buffer) - 1;
	while (buffer[i] == ' ')
	{
		buffer[i] = '\0';
		i--;
	}
	while (*buffer == ' ')
		buffer++;
	return (buffer);
}

char	*ft_end_buffer(char *ret, char **save)
{
	*save = NULL;
	if (ft_is_only_space(ret))
		return (NULL);
	return (ret);
}

char	*ft_strtok(char *buffer, char sep)
{
	static char	*save;
	char *ret;
	
	if (!save)
		save = buffer;
	ret = save;
	while (save && *save == ' ')
		save++;
	while (save && *save != sep)
	{
		if (*save == '\0')
			return (ft_end_buffer(ret, &save));
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
		*save++ = '\0';
	return (ret);
}

int	ft_token_count(char *buffer, char sep)
{
	char *tmp;
	char *token;
	int i;
	
	i = 0;
	tmp = ft_strdup(buffer);
	token = ft_trim_space(ft_strtok(tmp, sep));
	while(token)
	{
		i++;
		token = ft_trim_space(ft_strtok(NULL, sep));
	}
	free(tmp);
	return (i);
}

void	ft_make_cmd_table(t_data *data)
{
	int i;

	i = 0;
	data->cmd_count = ft_token_count(data->buffer, '|');
	data->cmd = ft_calloc(sizeof(t_cmd), data->cmd_count + 1);
	if (data->cmd == NULL)
		ft_exit(data, "Malloc error\n", 2);
	data->cmd[0].buffer = ft_trim_space(ft_strtok(data->buffer, '|'));
	while (++i < data->cmd_count)
		data->cmd[i].buffer = ft_trim_space(ft_strtok(NULL, '|'));
}

void	ft_make_token(t_data *data)
{
	int c;
	int t;
	int count;

	c = -1;
	while (++c < data->cmd_count)
	{
		count = ft_token_count(data->cmd[c].buffer, ' ');
		data->cmd[c].token = ft_calloc(sizeof(char *), count + 1);
		t = 0;
		data->cmd[c].token[t] = ft_trim_space(ft_strtok(data->cmd[c].buffer, ' '));
		while (++t < count)
			data->cmd[c].token[t] = ft_trim_space(ft_strtok(NULL, ' '));
	}
}

void 	ft_parse(t_data *data)
{
	ft_make_cmd_table(data);
	ft_make_token(data);
	ft_print_table(data);
}

/* ***********************MAIN*********************************************** */

int	main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	t_data data;

	ft_init_environement(&data, env);// Copy global environ variable to heap
	while (1)
	{
		data.prompt = ft_get_prompt();// Get user and path for prompt
		data.buffer = readline(data.prompt);// Fill the buffer with user input
		free(data.prompt);// Free the prompt for next iteration
		if (ft_is_only_space(data.buffer))// Newline on empty buffer
			free(data.buffer);
		else if (ft_strncmp(data.buffer, "exit", 5) == 0)// Exit on exit command
			ft_exit(&data, "Goodbye\n", 2);
		else
		{
			ft_parse(&data);//tokenize the buffer
			//ft_execute(&data);//execute the command
			ft_free_table(&data);// Free the table for next iteration
		}
	}
}

/*
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
*/
