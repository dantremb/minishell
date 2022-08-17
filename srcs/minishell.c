/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/17 13:15:14 by dantremb         ###   ########.fr       */
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

void	ft_free_command_table(t_data *data)
{
	int	i;
	
	i = -1;
	while (data->cmds[++i].id)
	{
		if (data->cmds[i].cmd)
			free (data->cmds[i].cmd);
		data->cmds[i].cmd = NULL;
		free (data->cmds[i].path);
		data->cmds[i].path = NULL;
		free (data->cmds[i].cmd_buffer);
		data->cmds[i].cmd_buffer = NULL;
		ft_free_array(data->cmds[i].options);
		data->cmds[i].options = NULL;
	}
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

bool	ft_is_only_space(char *buffer)ls -al

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

char	**ft_split_command(char *buffer)
{
	char	**tmp;

	tmp = ft_split(buffer, ' ');
	return (tmp);
}

char *ft_get_command_path(char *cmd)
{
	char	*program_name;
	char	**prog_path;
	char	*env_path;
	char	*test_path;
	int		i;
	
	if (!cmd || access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	program_name = ft_strjoin("/", cmd, 0);
	env_path = getenv("PATH");
	prog_path = ft_split(env_path, ':');
	if (prog_path == NULL)
		return (NULL);
	i = 0;
	while (prog_path[i])
	{
		test_path = ft_strjoin(prog_path[i], program_name, 0);
		if (access(test_path, F_OK | X_OK) == 0)
			break ;
		free (test_path);
		i++;
	}
	//ft_free_array(prog_path);
	//free (program_name);
	return (test_path);
}

void	ft_init_command_table(t_cmd *cmd, int id, char *buffer)
{
	ft_color(RED);
	printf("Init command #%d\n", id);
	cmd->cmd_buffer = buffer;
	ft_color(YELLOW);
	printf("[  BUFFER] : %s\n", cmd->cmd_buffer);
	cmd->id = id;
	printf("[      ID] : %d\n", cmd->id);
	cmd->infile = 0;
	cmd->outfile = 0;
	cmd->cmd = NULL;
	cmd->options = ft_split(buffer, ' ');
	int i = -1;
	printf("[ OPTIONS] : ");
	while (cmd->options[++i])
		printf("[%s]", cmd->options[i]);
	printf("\n");
	cmd->path = ft_get_command_path(cmd->options[0]);
	printf("[    PATH] : %s\n", cmd->path);
	ft_color(WHITE);
}

void	ft_parse_command(t_data *data, int count)
{
	ft_color(BLUE);
	printf("[--- PARSING %d COMMANDS ---]\n", count);
	ft_color(WHITE);
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

void	ft_child_process(t_data *data, t_cmd *cmd)
{
	printf("White \033[0;37m");
	execve(cmd->path, cmd->options, environ);
	(void)data;
}

void	ft_execute_command(t_data *data, t_cmd *cmd)
{
	//int ret;
	pid_t pid;
	
	ft_color(1);
	printf("execute command no.%d\n", cmd->id);
	pid = fork();
	if (pid == 0)
		ft_child_process(data, cmd);
	else
		waitpid(pid, NULL, 0);
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
		printf("export\n");
	else if (ft_strncmp(cmd->cmd_buffer, "unset ", 6) == 0)
		printf("unset\n"); 
	else if (ft_strncmp(cmd->cmd_buffer, "pwd", 3) == 0)
		printf("pwd\n");
	else if (ft_strncmp(cmd->cmd_buffer, "env", 3) == 0)
		ft_env();
	else if (ft_strncmp(cmd->cmd_buffer, "exit", 4) == 0)
		ft_exit(data, "Good bye!\n", 4);
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
	ft_color(CYAN);
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
		else
		{
			ft_parse_command(&data, ft_number_of_command(data.buffer));
			ft_execute_command_table(&data);// Execute Command
			//ft_free_command_table(&data);
		}
		free (data.buffer);
	}
	ft_free_array(environ);
}
