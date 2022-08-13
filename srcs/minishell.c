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

/* ********************EXIT************************************************** */

void	ft_exit(t_data *data, char *str, int s)
{
	ft_putstr_fd(str, 2);
	if (s < 1)
		exit(0);
	if (s < 2)
		free(data->buffer);
	if (s < 3)
		ft_free_array(data->env);
	if (s < 4)
		free(data->buffer);
	else if (s == 3)
	{
		free(data->buffer);
		ft_free_array(data->env);
		free(data->cmds);
		ft_free_cmd_buffer(data);
		exit(0);
	}
}

void	ft_free

/* **********************INIT ENVIRONEMENT*********************************** */

void	ft_copy_env(t_data *data, char **envp)
{
	printf("copy environement\n");
	int i;

	i = 0;
	data->env = ft_calloc(sizeof(char *), ft_array_size(envp));
	if (data->env == NULL)
		ft_exit(data, "Malloc error\n", 0);
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
			ft_exit(data, "Malloc error\n", 0);
		i++;
	}
}

void	ft_init_environement(t_data *data, char **envp)
{
	printf("Init environment\n");
	data->nb_cmd = 0;
	data->buffer = NULL;
	data->env = NULL;
	data->prompt = NULL;
	data->cmds = NULL;
	ft_copy_env(data, envp);
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

void	ft_init_command_table(t_cmd *cmd, int id, char *buffer)
{
	printf("Init command #%d\n", id);
	cmd->id = id;
	cmd->infile = 0;
	cmd->outfile = 0;
	cmd->builtin = 0;
	cmd->options = NULL;
	cmd->path = NULL;
	cmd->cmd = NULL;
	cmd->cmd_buffer = buffer;
	printf("my buffer is %s\n", cmd->cmd_buffer);
}

void	ft_parse_command(t_data *data, int count)
{
	printf("parsing %d commands\n", count);
	int		i;
	char	**split;

	split = ft_split(data->buffer, ';');
	if (split == NULL)
		ft_exit(data, "Malloc error\n", 1);
	data->nb_cmd = count;
	data->cmds = ft_calloc(sizeof(t_cmd), count);
	if (data->cmds == NULL)
	{
		ft_free_array(split);
		ft_exit(data, "Malloc error\n", 1);
	}
	i = -1;
	while (++i < count)
		ft_init_command_table(&data->cmds[i], i + 1, split[i]);
	free(split);
}

/* *******************ENGINE************************************************* */

void	ft_execute_command(t_cmd *cmd)
{
	printf("execute command no.%d\n", cmd->id);
}

void	ft_execute_command_table(t_data *data)
{
	printf("execute the table\n");
	int	i;

	i = -1;
	while (++i < data->nb_cmd)
		ft_execute_command(&data->cmds[i]);
}

/* ******************BUILT-IN************************************************ */

void	ft_env(t_data *data)
{
	int	i;

	i = -1;
	while(data->env[++i])
		printf("%s\n", data->env[i]);

}

/* ***********************MAIN*********************************************** */

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	(void)argc;
	(void)argv;

	ft_init_environement(&data, envp);
	while (1)
	{
		data.prompt = ft_get_prompt();
		data.buffer = readline(data.prompt);
		free(data.prompt);
		if (ft_is_only_space(data.buffer))// Newline on empty buffer
			continue ;
		else if (ft_strncmp(data.buffer, "env", 3) == 0)// Environement
			ft_env(&data);
		else if (ft_strncmp(data.buffer, "exit", 4) == 0)// exit program
			ft_exit(&data, "Good bye, have a nice day!\n", 2);
		else
		{
			ft_parse_command(&data, ft_number_of_command(data.buffer));
			free(data.cmds);
			ft_free_cmd_buffer(&data);
			printf("Execute Command\n");// Execute Command
		}
		free (data.buffer);
	}
}
