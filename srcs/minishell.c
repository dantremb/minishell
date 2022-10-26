/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/26 11:32:25 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	ft_getprompt(shell_t *shell)
{
	shell->buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
	while (shell->buffer != NULL)
	{
		if (shell->buffer[0] == 4)
			printf("\n");
		else if (!ft_is_only(shell->buffer, ' '))
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

shell_t	*ft_init_minishell(char **env)
{
	shell_t *shell;

	error_status = 0;
	shell = ft_calloc(1, sizeof(shell_t));
	if (!shell)
		ft_exit(shell, "Error: malloc failed\n", 15);
	shell->expand[0] = 'a';
	shell->heredoc[0] = 'a';
	shell->env = ft_remalloc(env, 0, 0);
	if (shell->env == NULL){
		ft_exit(shell, "Error: malloc failed\n", 15);
	}
	shell->save_fd[0] = dup(STDIN_FILENO);
	shell->save_fd[1] = dup(STDOUT_FILENO);
	return (shell);
}

void	ft_minishell(char **env)
{
	shell_t *shell;

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