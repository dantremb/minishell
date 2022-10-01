/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main->c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student->42->fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:49:16 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/30 22:56:22 by dantremb         ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int error_status;

int	main(int ac, char **av, char **env)
{

	t_shell *shell;
	
	shell = ft_init_minishell(ac, av, env);
	signal(SIGINT, ft_signal);
	ft_getprompt(shell);
	ft_exit(shell, "Goodbye\n", 0, 2);
}

/***environement***/

t_shell	*ft_init_minishell(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_shell *shell;

	error_status = 0;
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		ft_putstr_fd("Error: malloc failed\n", 2);
	shell->env = ft_remalloc(env, 0, 0);
	if (shell->env == NULL){
		free(shell);
		ft_putstr_fd("Error: malloc failed\n", 2);
	}
	return (shell);
}

/***parsing***/

int	ft_status(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->buffer[i] && (shell->buffer[i] == ' ' || shell->buffer[i] == '\t'))
		i++;
	if (shell->buffer[i] == '$' && shell->buffer[i + 1] == '?')
	{
		printf("%d: command not found\n", error_status);
		error_status = 0;
		return (1);
	}
	return (0);
}

int	ft_check_closed_quote(char *buf)
{
	int	i;
	int	d;
	int	s;

	i = -1;
	d = 0;
	s = 0;
	while (buf[++i]){
		if (buf[i] == '\"')
			d++;
		if (buf[i] == '\'')
			s++;
	}
	if ((d && (d % 2) != 0) || (s && (s % 2)) != 0){
		printf("Error Quote not closed\n");
		return (0);
	}
	return (1);
}

int 	ft_parse(t_shell *shell)
{
	int i;

	i = 0;
	if (ft_check_closed_quote(shell->buffer) == 0 || ft_status(shell))
		return (0);
	shell->nb_cmd = ft_token_count(shell->buffer, '|');
	shell->cmd = ft_calloc(sizeof(t_cmd), shell->nb_cmd);
	if (shell->cmd == NULL)
		ft_exit(shell, "Error: malloc failed\n", 15, 3);
	shell->cmd[0].buffer = ft_trim_token(ft_strtok(shell->buffer, '|'), ' ');
	while (++i < shell->nb_cmd)
		shell->cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' ');
	//ft_parse_token();
	return (1);
}

/***get prompt***/

int	ft_getprompt(t_shell *shell)
{
	shell->buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
	while (shell->buffer != NULL)
	{
		if (!ft_is_only(shell->buffer, ' '))
		{
			add_history(shell->buffer);
			if (ft_parse(shell)){
				ft_printf("Execute %d cmd(s)\n", shell->nb_cmd);
				if (ft_strncmp(shell->cmd[0].buffer, "exit\0", 5) == 0) {
					ft_free(shell, 8);
					break ;
				}
				ft_free(shell, 8);
			}
			else
				ft_free(shell, 9);
		}
		shell->buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
	}
	return (0);
}

/***exit and free***/

void	ft_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		error_status = 130;
	}
}

void	ft_free(t_shell *shell, int flag)
{
	if (flag == 1)
		free(shell);
	if (flag <= 2)
		ft_free_array(shell->env);
	if (flag >= 8)
		free(shell->cmd);
	if (flag == 9)
		free(shell->buffer);
}

void	ft_exit(t_shell *shell, char *msg, int status, int flag)
{
	ft_putstr_fd(msg, 2);
	ft_free(shell, flag);
	exit(status);
}
