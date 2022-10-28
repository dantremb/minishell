/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/27 20:44:01 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error_status;

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
