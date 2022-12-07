/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:51:07 by dantremb          #+#    #+#             */
/*   Updated: 2022/12/07 11:21:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**g_env;

static void	ft_interactive(int signal)
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

static void	ft_interupt(int signal)
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
