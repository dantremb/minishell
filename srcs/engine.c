/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 00:33:28 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/31 15:54:29 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_error_status;

bool	ft_execute_builtin(t_shell *shell, int nb)
{
	if (ft_strncmp(shell->cmd[nb].token[0], "echo", 4) == 0)
		ft_echo(shell->cmd[nb].token);
	else if (ft_strncmp(shell->cmd[nb].token[0], "env", 3) == 0)
		ft_env(shell, 1);
	else if (ft_strncmp(shell->cmd[nb].token[0], "unset\0", 6) == 0)
		ft_unset(shell, shell->cmd[nb].token[1]);
	else if (ft_strncmp(shell->cmd[nb].token[0], "pwd\0", 4) == 0)
		printf("%s\n", ft_get_variable(shell, "PWD", 0));
	else if (ft_strncmp(shell->cmd[nb].token[0], "export", 6) == 0)
		ft_export(shell, shell->cmd[nb].token[1], 1);
	else if (ft_strncmp(shell->cmd[nb].buffer, "cd", 2) == 0)
		ft_cd(shell, shell->cmd[nb].token[1]);
	else if (ft_strncmp(shell->cmd[nb].token[0], "exit\0", 5) == 0)
		ft_exit(shell, "Goodbye\n", 0);
	else
		return (false);
	return (true);
}

void	ft_exec_cmd(t_shell *shell, int nb)
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_exit(shell, "pipe error\n", 14);
	shell->pid[nb] = fork();
	if (shell->pid[nb] == 0)
	{
		if (nb < shell->nb_cmd - 1)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
		}
		ft_find_redirect(shell, nb);
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
	{
		waitpid(pid, &status, 0);
	}
	return (status);
}

int	ft_execute_solo(t_shell *shell, int nb)
{
	int	status;

	status = 0;
	ft_find_redirect(shell, nb);
	shell->pid[nb] = fork();
	if (shell->pid[nb] == 0)
		ft_execve(shell, nb);
	else
	{
		waitpid(shell->pid[nb], &g_error_status, 0);
		dprintf(2, "parent fd in = %d, out = %d\n", shell->cmd[0].fd_in ,shell->cmd[0].fd_out);
		if (shell->cmd[0].fd_in > 2)
			close(shell->cmd[0].fd_in);
		if (shell->cmd[0].fd_out > 2)
			close(shell->cmd[0].fd_out);
	}
	return (status);
}

void	ft_execute_cmd(t_shell *shell, int nb)
{
	char	*status;
	char	*export_status;

	if (shell->nb_cmd > 1)
		g_error_status = ft_subshell(shell, nb);
	else
		g_error_status = ft_execute_solo(shell, nb);
	status = ft_itoa(g_error_status);
	export_status = ft_strjoin("?=", status, 0);
	ft_export(shell, export_status, 0);
	free (export_status);
	free (status);
}
