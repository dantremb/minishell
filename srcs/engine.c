/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 00:33:28 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/22 00:54:58 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
extern t_data data;

bool	ft_execute_builtin(int nb)
{
	if (ft_strncmp(data.cmd[nb].token[0], "echo", 4) == 0)
		ft_echo(data.cmd[nb].token);
	else if (ft_strncmp(data.cmd[nb].token[0], "env", 3) == 0)
		ft_env(1);
	else if (ft_strncmp(data.cmd[nb].token[0], "export", 6) == 0)
		ft_export(data.cmd[nb].token[1]);
	else if (ft_strncmp(data.cmd[nb].token[0], "unset\0", 6) == 0)
		ft_unset(data.cmd[nb].token[1]);
	else if (ft_strncmp(data.cmd[nb].token[0], "pwd\0", 4) == 0)
		printf("%s\n", ft_get_variable("PWD"));
	else if (ft_strncmp(data.cmd[nb].buffer, "cd", 2) == 0)
		ft_cd(data.cmd[nb].token[1]);
	else if (ft_strncmp(data.cmd[nb].token[0], "exit\0", 5) == 0)
		ft_exit("Goodbye\n", 3);
	else
		return (false);
	return (true);
}
void	ft_execve(int nb)
{
	char	*cmd_path;
	
	ft_clean_token(data.cmd[nb].token);
	if (ft_execute_builtin(nb) == false)
	{
		cmd_path = ft_get_path(nb);
		if (execve(cmd_path, data.cmd[nb].token, data.env))
			printf("%s: command not found\n", data.cmd[nb].token[0]);
	}
	exit(0);
}

void	ft_exec_cmd(int nb)
{
	int	fd[2];
	
	if(pipe(fd) == -1)
		ft_exit("pipe error\n", 3);
	data.cmd[nb].pid = fork();
	if (data.cmd[nb].pid == 0)
	{
		if (nb < data.cmd_count - 1)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
		}
		ft_execve(nb);
	}
	else if (nb < data.cmd_count - 1)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

void	ft_execute_cmd(int nb)
{
	int old_stdin;
	
	old_stdin = dup(STDIN_FILENO);
	while (nb < data.cmd_count) 
		ft_exec_cmd(nb++);
	nb = 0;
	while (nb < data.cmd_count)
		waitpid(data.cmd[nb++].pid, NULL, 0);
	dup2(old_stdin, STDIN_FILENO);
}
