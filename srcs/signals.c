/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:51:07 by dantremb          #+#    #+#             */
/*   Updated: 2022/11/23 23:04:14 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_interactive(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
		rl_redisplay();
}

void	ft_signal_on(void)
{
	signal(SIGINT, ft_interactive);
	signal(SIGQUIT, ft_interactive);
}

void	ft_interupt(int signal)
{
	if (signal == SIGINT)
	{
		kill(0, 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
	}
	if (signal == SIGQUIT)
	{
		kill(0, 0);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
	}
}

void	ft_signal_off(void)
{
	signal(SIGINT, ft_interupt);
	signal(SIGQUIT, ft_interupt);
}

void	ft_clear_command(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < shell->nb_cmd)
		ft_free(shell->cmd[i].save);
	shell->cmd = ft_free(shell->cmd);
	shell->pid = ft_free(shell->pid);
	shell->buffer = ft_free(shell->buffer);
	shell->nb_cmd = 0;
	shell->expand[0] = 'a';
	shell->heredoc[0] = 'a';
	ft_clear_fd();
}
