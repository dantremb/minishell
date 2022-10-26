/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 01:18:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/26 11:32:09 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	ft_make_heredoc(shell_t *shell, char *limiter, char *heredoc)
{
	int		fd;
	char	*str;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, ft_heredoc_signal);
		fd = ft_open_fd(heredoc, 2);
		if (fd == -1)
			ft_exit(shell, "Error: heredoc file not found", 1);
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
		free(str);
		close(fd);
	}
	else
		waitpid(pid, NULL, 0);
}

char	*ft_expand_heredoc(shell_t *shell, char *heredoc)
{
	char	*temps;
	char	*expand;

	expand = ft_strjoin("<", shell->heredoc, 0);
	expand = ft_strjoin(expand, "=", 1);
	temps = ft_strjoin(expand, heredoc, 0);
	free(heredoc);
	ft_export(shell, temps, 0);
	free(temps);
	expand[ft_strlen(expand) - 1] = '\0';
	temps = ft_get_variable(shell, expand, 0);
	free(expand);
	shell->heredoc[0] = shell->heredoc[0] + 1;
	return (temps);
}

void	ft_parse_heredoc(shell_t *shell, char **token)
{
	int i;
	char	*str;

	i = -1;
	while (token[++i])
	{
		if (ft_strncmp(token[i], "<<", 2) == 0)
		{
			if (token[i][2] == '\0')
			{
				str = ft_expand_heredoc(shell, ft_strjoin("<", shell->heredoc, 0));
				ft_make_heredoc(shell, token[i + 1], str);
				token[i][1] = '\0';
				token[i + 1] = str + 1;
			}
			else
			{
				str = ft_expand_heredoc(shell, ft_strjoin("<", shell->heredoc, 0));
				ft_make_heredoc(shell, &token[i][2], str);
				token[i] = str;
			}
		}
	}
}

void	ft_parse_token(shell_t *shell)
{
	int c;
	int t;

	c = -1;
	while (++c < shell->nb_cmd)
	{
		shell->cmd[c].nb_token = ft_token_count(shell->cmd[c].buffer, ' ');
		shell->cmd[c].token = ft_calloc(sizeof(char *), shell->cmd[c].nb_token + 1);
		if (!shell->cmd[c].token)
			ft_exit(shell, "Error: malloc failed\n", 15);
		t = 0;
		shell->cmd[c].token[t] = ft_strtok(shell->cmd[c].buffer, ' ');
		while (shell->cmd[c].token[t++])
			shell->cmd[c].token[t] = ft_strtok(NULL, ' ');
		shell->cmd[c].save = shell->cmd[c].token;
		ft_print_table(shell);
		ft_parse_heredoc(shell, shell->cmd[c].token);
		ft_print_table(shell);
	}
}

int 	ft_parse(shell_t *shell)
{
	int i;

	i = 0;
	if (ft_buffer_integrity(shell) == 0)
		return (0);
	shell->nb_cmd = ft_token_count(shell->buffer, '|');
	shell->cmd = ft_calloc(sizeof(shell_t), shell->nb_cmd);
	shell->pid = ft_calloc(sizeof(pid_t), shell->nb_cmd);
	if (shell->pid == NULL || shell->cmd == NULL)
		ft_exit(shell, "Error: malloc failed\n", 15);
	shell->cmd[0].buffer = ft_trim_token(ft_strtok(shell->buffer, '|'), ' ');
	while (++i < shell->nb_cmd)
		shell->cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' ');
	ft_parse_token(shell);
	return (1);
}
