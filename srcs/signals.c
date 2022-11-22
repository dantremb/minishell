/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:51:07 by dantremb          #+#    #+#             */
/*   Updated: 2022/11/22 18:35:58 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_rl_reset(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal_on(void)
{
	struct sigaction	signal;

	ft_memset(&signal, 0, sizeof(signal));
	signal.sa_handler = &ft_rl_reset;
	sigaction(SIGINT, &signal, NULL);
}

void	ft_interupt_signal(int signal)
{
	(void)signal;
	rl_on_new_line();
}

void	ft_signal_off(void)
{
	struct sigaction	signal;

	ft_memset(&signal, 0, sizeof(signal));
	signal.sa_handler = &ft_interupt_signal;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
}
