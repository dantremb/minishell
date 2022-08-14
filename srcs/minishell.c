/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/14 11:46:12 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char **environ;
bool	ft_cd(char *buffer);

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

void	ft_free_command_table(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->nb_cmd)
		free(data->cmds[i].cmd_buffer);
}

void	ft_exit(t_data *data, char *str, int s)
{
	if (s <= 0)
		ft_putstr_fd(str, 2);
	if (s <= 1)
		free(data->buffer);
	if (s <= 2)
		ft_free_array(environ);
	if (s <= 3)
		free(data->cmds);
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
	cmd->cmd_buffer = buffer;
	cmd->id = id;
	cmd->infile = 0;
	cmd->outfile = 0;
	cmd->options = NULL;
	cmd->path = NULL;
	cmd->cmd = NULL;
	printf("my buffer is %s\n", cmd->cmd_buffer);
}

void	ft_parse_command(t_data *data, int count)
{
	printf("parsing %d commands\n", count);
	int		i;
	char	**split;

	data->nb_cmd = count;
	data->cmds = ft_calloc(sizeof(t_cmd), count);
	if (data->cmds == NULL)
		ft_exit(data, "Malloc error\n", 2);
	split = ft_split(data->buffer, ';');
	if (split == NULL)
		ft_exit(data, "Malloc error\n", 3);
	i = -1;
	while (++i < count)
		ft_init_command_table(&data->cmds[i], i + 1, split[i]);
	free(split);
}

/* *******************ENGINE************************************************* */

void	ft_execute_command(t_data *data, t_cmd *cmd)
{
	printf("execute command no.%d = %s\n", cmd->id, cmd->cmd_buffer);
	(void)data;
}

bool	ft_execute_builtin(t_data *data, t_cmd *cmd)
{
	(void)data;
	if (ft_strncmp(cmd->cmd_buffer, "echo ", 5) == 0)
		ft_echo(cmd->cmd_buffer + 5);
	else if (ft_strncmp(cmd->cmd_buffer, "cd ", 3) == 0)
		printf("cd\n");
	else if (ft_strncmp(cmd->cmd_buffer, "export ", 7) == 0)
		ft_cd(cmd->cmd_buffer + 7);
	else if (ft_strncmp(cmd->cmd_buffer, "unset ", 6) == 0)
		printf("unset\n");
	else if (ft_strncmp(cmd->cmd_buffer, "pwd ", 4) == 0)
		printf("pwd\n");
	else if (ft_strncmp(cmd->cmd_buffer, "env", 3) == 0)
		ft_env();
	else
		return (false);
	printf("bypass command no.%d = %s\n", cmd->id, cmd->cmd_buffer);
	return (true);
}

void	ft_execve_or_builtin(t_data *data, t_cmd *cmd)
{
	if (!ft_execute_builtin(data, cmd))
		ft_execute_command(data, cmd);
}

void	ft_execute_command_table(t_data *data)
{
	printf("execute the table\n");
	int	i;

	i = -1;
	while (++i < data->nb_cmd)
		ft_execve_or_builtin(data, &data->cmds[i]);
}


/* ***********************MAIN*********************************************** */

int	main(void)
{
	t_data data;

	ft_init_environement(&data);
	while (1)
	{
		data.prompt = ft_get_prompt();
		data.buffer = readline(data.prompt);
		free(data.prompt);
		if (ft_is_only_space(data.buffer))// Newline on empty buffer
			continue ;
		/* else if (ft_strncmp(data.buffer, "env", 3) == 0)// Environement
			ft_env(); */
		else if (ft_strncmp(data.buffer, "exit", 4) == 0)// exit program
			ft_exit(&data, "Good bye, have a nice day!\n", 2);
		else
		{
			ft_parse_command(&data, ft_number_of_command(data.buffer));
			ft_execute_command_table(&data);// Execute Command
			ft_free_command_table(&data);
		}
		free (data.buffer);
	}
	ft_free_array(environ);
}
