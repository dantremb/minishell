/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/11/23 10:41:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**g_env;

void	ft_clear_command(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < shell->nb_cmd)
		ft_free(shell->cmd[i].save);
	ft_free(shell->pid);
	ft_free(shell->cmd);
	ft_free(shell->buffer);
	ft_memset(shell, 0, sizeof(t_shell));
	shell->expand[0] = 'a';
	shell->heredoc[0] = 'a';
	ft_clear_fd();
}

void	ft_exit(t_shell *shell, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_clear_command(shell);
	ft_free_array(g_env);
	exit(1);
}

void	ft_init_shell(t_shell *shell, char **env, int ac, char **av)
{
	(void)ac;
	(void)av;
	g_env = NULL;
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
