/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/11/21 16:13:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**g_env;

void	ft_print_table(t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	while (++i < shell->nb_cmd)
	{
		dprintf(2, "\033[1;33m------------ TOKEN -----------------\n\033[0;0m");
		ft_color(3);
		dprintf(2, "\033[1;34mcmd %d\033[0;0m = \t", i);
		j = -1;
		while (++j < shell->cmd[i].nb_token)
			dprintf(2, "[\033[1;34m%s\033[1;33m]", shell->cmd[i].token[j]);
		dprintf(2, "\n");
		dprintf(2, "\033[1;33m------------------------------------\n\033[0;0m");
	}
}
void	ft_rl_newline(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal_off(void)
{
	struct sigaction	signal;

	ft_memset(&signal, 0, sizeof(signal));
	signal.sa_handler = &ft_rl_newline;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
}

void	ft_rl_reset(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signal_on(void)
{
	struct sigaction	signal;

	ft_memset(&signal, 0, sizeof(signal));
	signal.sa_handler = &ft_rl_reset;
	sigaction(SIGINT, &signal, NULL);
}

void	ft_clear_command(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < shell->nb_cmd)
		ft_free(shell->cmd[i].token);
	ft_free(shell->pid);
	ft_free(shell->cmd);
	ft_free(shell->buffer);
	ft_memset(shell, 0, sizeof(t_shell));
	shell->expand[0] = 'a';
	shell->heredoc[0] = 'a';
}

void	ft_exit(t_shell *shell, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_clear_command(shell);
	ft_free_array(g_env);
	exit(1);
}

char	*ft_get_variable(char *buffer, int flag)
{
	int		i;

	i = -1;
	if (!buffer)
		return (NULL);
	while (g_env[++i])
	{
		if (ft_strncmp(g_env[i], buffer, ft_strlen(buffer)) == 0)
		{
			if (g_env[i][ft_strlen(buffer)] == '=')
				return (g_env[i] + (ft_strlen(buffer) + 1));
		}
	}
	if (flag == 1)
		buffer[0] = '\0';
	return (buffer);
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
			printf("BOOM!!! buffer ==== [%s]\n", shell.buffer);
		//ft_print_table(&shell);
		ft_clear_command(&shell);
	}
	return (0);
}
