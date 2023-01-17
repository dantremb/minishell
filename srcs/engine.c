/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 00:33:28 by dantremb          #+#    #+#             */
/*   Updated: 2023/01/06 14:02:49 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**g_env;

bool	ft_execute_builtin(t_shell *shell, int nb)
{
	shell->error = 0;
	if (ft_strncmp(shell->cmd[nb].token[0], "echo\0", 5) == 0)
		ft_echo(shell->cmd[nb].token);
	else if (ft_strncmp(shell->cmd[nb].token[0], "env\0", 4) == 0)
		ft_env(1);
	else if (ft_strncmp(shell->cmd[nb].token[0], "unset\0", 6) == 0)
		ft_parse_unset(shell, nb);
	else if (ft_strncmp(shell->cmd[nb].token[0], "pwd\0", 4) == 0)
		printf("%s\n", ft_get_variable("PWD", 0));
	else if (ft_strncmp(shell->cmd[nb].token[0], "export\0", 7) == 0)
		ft_parse_export(shell, nb);
	else if (ft_strncmp(shell->cmd[nb].buffer, "cd\0", 3) == 0)
		ft_cd(shell, shell->cmd[nb].token[1]);
	else if (ft_strncmp(shell->cmd[nb].token[0], "exit\0", 5) == 0)
	{
		ft_unlink_heredoc(shell);
		ft_exit(shell, "Goodbye\n", 1);
	}
	else
		return (false);
	return (true);
}

static void	ft_exec_cmd(t_shell *shell, int nb)
{
	int		fd[2];

	if (pipe(fd) == -1)
		ft_exit(shell, "pipe error\n", 1);
	shell->pid[nb] = fork();
	if (shell->pid[nb] == 0)
	{
		if (nb < shell->nb_cmd - 1 )
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
		}
		ft_find_redirect(shell, nb);
		if (shell->cmd[nb].open_error == 1)
			return ;
		if (ft_execute_builtin(shell, nb) == false)
			ft_execve(shell, nb);
		else
			exit(0);
	}
	else if (nb < shell->nb_cmd - 1)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

int	ft_subshell(t_shell *shell, int nb)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		while (nb < shell->nb_cmd)
			ft_exec_cmd(shell, nb++);
		nb = 0;
		while (nb < shell->nb_cmd)
			waitpid(shell->pid[nb++], &status, 0);
		ft_exit(shell, NULL, status);
	}
	else
		waitpid(pid, &shell->error, 0);
	return (status);
}

static int	ft_execute_solo(t_shell *shell, int nb)
{
	ft_find_redirect(shell, nb);
	if (shell->cmd[nb].open_error == 1)
		return (1);
	if (ft_execute_builtin(shell, nb) == false)
	{
		shell->pid[nb] = fork();
		if (shell->pid[nb] == 0)
			ft_execve(shell, nb);
		waitpid(shell->pid[nb], &shell->error, 0);
	}
	return (0);
}

void	ft_execute_cmd(t_shell *shell, int nb)
{
	int		save_stdout;
	int		save_stdin;

	save_stdout = dup(STDOUT_FILENO);
	save_stdin = dup(STDIN_FILENO);
	if (shell->nb_cmd > 1)
		ft_subshell(shell, nb);
	else
		ft_execute_solo(shell, nb);
	if (shell->error == 256)
		shell->error = 127;
	ft_export_error(shell);
	dup2(save_stdout, STDOUT_FILENO);
	dup2(save_stdin, STDIN_FILENO);
}
