/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/11/23 22:24:14 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**g_env;

void	ft_parse_export(t_shell *shell, int nb)
{
	int	i;

	if (shell->cmd[nb].nb_token == 1)
		ft_env(0);
	else
	{
		i = 0;
		while (++i < shell->cmd[nb].nb_token)
			ft_export(shell->cmd[nb].token[i], 1);
	}
}

void	ft_parse_unset(t_shell *shell, int nb)
{
	int	i;

	i = 0;
	while (++i < shell->cmd[nb].nb_token)
		ft_unset(shell->cmd[nb].token[i]);
}

void	ft_exit(t_shell *shell, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_clear_command(shell);
	g_env = (char **)ft_free_array(g_env);
	rl_clear_history();
	exit(1);
}

void	ft_init_shell(t_shell *shell, char **env, int ac, char **av)
{
	(void)ac;
	(void)av;
	ft_memset(shell, 0, sizeof(t_shell));
	shell->expand[0] = 'a';
	shell->heredoc[0] = 'a';
	g_env = ft_remalloc(env, 0, 0);
	if (!g_env)
		ft_exit(shell, "Error: malloc failed\n");
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	ft_init_shell(&shell, env, ac, av);
	while (1)
	{
		ft_signal_on();
		shell.buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
		if (ft_parse(&shell) == 1)
		{
			ft_signal_off();
			ft_execute_cmd(&shell, 0);
		}
		ft_clear_command(&shell);
	}
	return (0);
}
