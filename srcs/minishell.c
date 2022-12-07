/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/12/07 11:21:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**g_env;

void	ft_print_table(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (i < shell->nb_cmd)
	{
		j = 0;
		ft_color(3);
		dprintf(2, "------------ TOKEN -----------------\n\033[0;0m");
		ft_color(3);
		dprintf(2, "cmd %d = \t", i);
		while (j < shell->cmd[i].nb_token)
		{
			ft_color(3);
			dprintf(2, "[\033[1;34m%s\033[1;33m]", shell->cmd[i].token[j]);
			j++;
		}
		dprintf(2, "\n");
		i++;
	}
	dprintf(2, "------------------------------------\n\033[0;0m");
}

void	ft_parse_export(t_shell *shell, int nb)
{
	int	i;

	if (shell->cmd[nb].nb_token == 1)
		ft_env(0);
	else
	{
		i = 0;
		while (++i < shell->cmd[nb].nb_token)
			ft_export(shell, shell->cmd[nb].token[i], 1);
	}
}

void	ft_parse_unset(t_shell *shell, int nb)
{
	int	i;

	i = 0;
	while (++i < shell->cmd[nb].nb_token)
		ft_unset(shell->cmd[nb].token[i]);
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

void	ft_exit(t_shell *shell, char *msg, int errno)
{
	ft_putstr_fd(msg, 2);
	ft_clear_command(shell);
	g_env = (char **)ft_free_array(g_env);
	rl_clear_history();
	exit(errno);
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
		ft_exit(shell, "Error: malloc failed\n", 1);
	ft_export_error(shell);
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
