/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/11/01 23:42:05 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error_status;

void	ft_parse_export(t_shell *shell, int nb)
{
	int	i;

	if (shell->cmd[nb].nb_token == 1)
		ft_env(shell, 0);
	else
	{
		i = 0;
		while (++i < shell->cmd[nb].nb_token)
			ft_export(shell, shell->cmd[nb].token[i], 1);
	}
}

static int	ft_getprompt(t_shell *shell)
{
	shell->buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
	while (shell->buffer != NULL)
	{
		if (!ft_is_only(shell->buffer, ' '))
		{
			add_history(shell->buffer);
			if (ft_parse(shell))
				ft_execute_cmd(shell, 0);
			ft_clear_command(shell);
		}
		else
			shell->buffer = ft_free(shell->buffer);
		shell->buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
	}
	return (0);
}

static t_shell	*ft_init_minishell(char **env)
{
	t_shell	*shell;

	g_error_status = 0;
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		ft_exit(shell, "Error: malloc failed\n", 15);
	shell->expand[0] = 'a';
	shell->heredoc[0] = 'a';
	shell->env = ft_remalloc(env, 0, 0);
	if (shell->env == NULL)
		ft_exit(shell, "Error: malloc failed\n", 15);
	return (shell);
}

static void	ft_minishell(char **env)
{
	t_shell	*shell;

	shell = ft_init_minishell(env);
	signal(SIGINT, ft_signal);
	ft_getprompt(shell);
	ft_exit(shell, "Goodbye\n", 0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_minishell(env);
	return (0);
}
