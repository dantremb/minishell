/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 01:18:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/31 15:47:08 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_error_status;

void	ft_heredoc_fork(char *limiter, char *heredoc)
{
	int		fd;
	char	*str;

	signal(SIGINT, ft_heredoc_signal);
	fd = ft_open_fd(heredoc, 2);
	if (fd == -1)
		exit(1);
	write(1, "heredoc> ", 9);
	str = ft_get_next_line(0);
	while (str)
	{
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0
			&& str[ft_strlen(limiter) + 1] == '\0')
			break ;
		ft_putstr_fd(str, fd);
		free(str);
		write(1, "heredoc> ", 9);
		str = ft_get_next_line(0);
	}
	ft_free(str);
	close(fd);
}

void	ft_make_heredoc(char *limiter, char *heredoc)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_heredoc_fork(limiter, heredoc);
	else
		waitpid(pid, &g_error_status, 0);
}

void	ft_parse_heredoc(t_shell *shell, char **token)
{
	int		i;
	char	*str;

	i = -1;
	while (token[++i])
	{
		if (ft_strncmp(token[i], "<<", 2) == 0)
		{
			if (token[i][2] == '\0')
			{
				str = ft_exp_heredoc(shell, ft_strjoin("<", shell->heredoc, 0));
				ft_make_heredoc(token[i + 1], str);
				token[i][1] = '\0';
				token[i + 1] = str + 1;
			}
			else
			{
				str = ft_exp_heredoc(shell, ft_strjoin("<", shell->heredoc, 0));
				ft_make_heredoc(&token[i][2], str);
				token[i] = str;
			}
		}
	}
}

void	ft_parse_token(t_shell *shell)
{
	int	c;
	int	t;

	c = -1;
	while (++c < shell->nb_cmd)
	{
		shell->cmd[c].nb_token = ft_token_count(shell->cmd[c].buffer, ' ');
		shell->cmd[c].token = ft_calloc(sizeof(char *),
				shell->cmd[c].nb_token + 1);
		if (!shell->cmd[c].token)
			ft_exit(shell, "Error: malloc failed\n", 15);
		t = 0;
		shell->cmd[c].token[t] = ft_strtok(shell->cmd[c].buffer, ' ');
		while (shell->cmd[c].token[t++])
			shell->cmd[c].token[t] = ft_strtok(NULL, ' ');
		shell->cmd[c].save = shell->cmd[c].token;
		ft_parse_heredoc(shell, shell->cmd[c].token);
		shell->cmd[c].fd_in = -1;
		shell->cmd[c].fd_out = -1;
	}
}

int	ft_parse(t_shell *shell)
{
	int	i;

	i = 0;
	if (ft_buffer_integrity(shell) == 0)
		return (0);
	shell->nb_cmd = ft_token_count(shell->buffer, '|');
	shell->cmd = ft_calloc(sizeof(t_cmd), shell->nb_cmd);
	shell->pid = ft_calloc(sizeof(pid_t), shell->nb_cmd);
	if (shell->pid == NULL || shell->cmd == NULL)
		ft_exit(shell, "Error: malloc failed\n", 15);
	shell->cmd[0].buffer = ft_trim_token(ft_strtok(shell->buffer, '|'), ' ');
	while (++i < shell->nb_cmd)
		shell->cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' ');
	ft_parse_token(shell);
	return (1);
}
