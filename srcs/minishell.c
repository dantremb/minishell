/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/09 16:47:02 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char **environ;

/* *******************UTILS************************************************** */

void	ft_exit_program(t_data *data, char *str, int status)
{
	ft_putstr_fd(str, 2);
	if (status == 0)
		exit (0);
	else if (status == 1)
	{
		ft_free_array(environ);
	}
	else if (status == 2)
	{
		ft_free_array(environ);
		free(data->buffer);
	}
	else
	{
		ft_free_array(environ);
		free(data->buffer);
		free(data->cmds);
	}
	exit(0);
}

void	ft_print_command_table(t_data *data)
{
	printf("Number of commands: %d\n", data->nb_cmd);
}

/* **********************INIT ENVIRONEMENT*********************************** */

void	ft_copy_environement(t_data *data)
{
	int i;
	char **tmp;

	i = 0;
	tmp = malloc(sizeof(char *) * (ft_array_size(environ)));
	if (tmp == NULL)
		ft_exit_program(data, "Malloc error\n", 0);
	printf("copy environement\n");
	while (environ[i])
	{
		tmp[i] = ft_strdup(environ[i]);
		if (!tmp[i++])
		{
			free(tmp);
			ft_exit_program(data, "Malloc error\n", 0);
		}
	}
	environ = tmp;
}

void	ft_init_environement(t_data *data)
{
	printf("%s\n", "Init environment");
	data->nb_cmd = 0;
	data->buffer = NULL;
	data->cmds = NULL;
	ft_copy_environement(data);
}

/* ************************READLINE UTILS************************************ */

char	*ft_get_prompt(void)
{
	char	*prompt;
	
	prompt = ft_strjoin("\033[0;32m", getenv("USER") , 0);
	prompt = ft_strjoin(prompt, "@", 1);
	prompt = ft_strjoin(prompt, getenv("NAME"), 1);
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

int	ft_is_builtin(t_cmd *cmds)
{
	if (ft_strncmp(cmds->cmd_buffer, "echo ", 5) == 0)
		return (1);
	else if (ft_strncmp(cmds->cmd_buffer, "cd", 2) == 0)
		return (2);
	else if (ft_strncmp(cmds->cmd_buffer, "pwd", 3) == 0)
		return (3);
	else if (ft_strncmp(cmds->cmd_buffer, "export ", 7) == 0)
		return (4);
	else if (ft_strncmp(cmds->cmd_buffer, "unset ", 9) == 0)
		return (5);
	else if (ft_strncmp(cmds->cmd_buffer, "env", 4) == 0)
		return (6);
	else if (ft_strncmp(cmds->cmd_buffer, "exit", 4) == 0)
		return (7);
	else
		return (0);
}

int	ft_number_of_command(char *buffer)
{
	int i;
	int count;

	i = 0;
	count = 1;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == ';')
			count++;
		i++;
	}
	return (count);
}

void	ft_fill_command_table(t_data *data)
{
	printf("fill the table\n");
	(void)data;
	//	if (ft_is_builtin(data->cmds[0]))
	//		ft_init_builtin(data->cmds[0]);
	//	else
	//		ft_init_execve(data->cmds[0]);
}

void	ft_parse_command(t_data *data, int count)
{
	char **split;

	printf("parsing %d commands\n", count);
	split = ft_split(data->buffer, ';');
	if (split == NULL)
		ft_exit_program(data, "Malloc error\n", 2);
	data->nb_cmd = count;
	printf("array size = %d and count = %d\n", ft_array_size(split) - 1, count);
	data->cmds = malloc(sizeof(t_cmd) * count);
	if (data->cmds == NULL)
		ft_exit_program(data, "malloc error", 2);
	//ft_init_command_table(data);
	//ft_fill_command_table(data);
}

/* *******************ENGINE************************************************* */

void	ft_execute_command_table(t_data *data)
{
	printf("execute the table\n");
	ft_print_command_table(data);
}

/* ******************BUILT-IN************************************************ */

void	ft_print_env(void)
{
	int	i;

	i = -1;
	while(environ[++i])
		printf("%s\n", environ[i]);

}

/* ***********************MAIN*********************************************** */

int	main(void)
{
	t_data data;
	
	ft_init_environement(&data);
	while (1)
	{
		data.buffer = readline(ft_get_prompt());
		if (ft_is_only_space(data.buffer))// if buffer is empty
			continue ;
		else if (ft_strncmp(data.buffer, "env", 3) == 0)
			ft_print_env();
		else if (ft_strncmp(data.buffer, "exit ", 4) == 0)// exit program
			ft_exit_program(&data, "Good bye, have a nice day!\n", 2);
		else
		{
			ft_parse_command(&data, ft_number_of_command(data.buffer));// parsing the buffer into the command table
			//ft_execute_command_table(&data);// executing the command table
			//free command table
			free (data.cmds);
		}
		free (data.buffer);
	}
}
