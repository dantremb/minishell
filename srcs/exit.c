/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:59:23 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/27 00:03:48 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int g_error_status;

void	ft_clear_command(shell_t *shell)
{
	int	i;
	i = -1;
	while (++i < shell->nb_cmd)
		ft_free(shell->cmd[i].save);
	shell->pid = ft_free(shell->pid);
	shell->cmd = ft_free(shell->cmd);
	shell->buffer = ft_free(shell->buffer);
	shell->nb_cmd = 0;
}

void	ft_exit(shell_t *shell, char *msg, int status)
{
	ft_putstr_fd(msg, 2);
	ft_clear_command(shell);
	ft_free_array(shell->env);
	shell = ft_free(shell);
	exit(status);
}

void	ft_heredoc_signal(int signal)
{
	if (signal == SIGINT)
	{
		exit(1);
	}
}

void	ft_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_error_status = 130;
	}
}