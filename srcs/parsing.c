/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:21:33 by dantremb          #+#    #+#             */
/*   Updated: 2022/11/21 16:12:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**g_env;

void	ft_make_heredoc(char *limiter, char *heredoc)
{
	int		fd;
	char	*str;

	ft_signal_off();
	fd = ft_open_fd(heredoc, 2);
	str = readline("heredoc > ");
	while (str)
	{
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
			break ;
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
		ft_free(str);
		str = readline("heredoc > ");
	}
	ft_free(str);
	close(fd);
	ft_signal_on();
}

char	*ft_expand_heredoc(t_shell *shell, char *heredoc)
{
	char	*temps;
	char	*expand;

	expand = ft_strjoin("<", shell->heredoc, 0);
	expand = ft_strjoin(expand, "=", 1);
	temps = ft_strjoin(expand, heredoc, 0);
	free(heredoc);
	ft_export(temps, 0);
	free(temps);
	expand[ft_strlen(expand) - 1] = '\0';
	temps = ft_get_variable(expand, 0);
	free(expand);
	shell->heredoc[0] = shell->heredoc[0] + 1;
	return (temps);
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
				str = ft_expand_heredoc(shell, ft_strjoin("<",
							shell->heredoc, 0));
				ft_make_heredoc(token[i + 1], str);
				token[i][1] = '\0';
				token[i + 1] = str;
			}
			else
			{
				str = ft_expand_heredoc(shell, ft_strjoin("<",
							shell->heredoc, 0));
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
			ft_exit(shell, "Error: malloc failed\n");
		t = 0;
		shell->cmd[c].token[t] = ft_strtok(shell->cmd[c].buffer, ' ');
		while (shell->cmd[c].token[t++])
			shell->cmd[c].token[t] = ft_strtok(NULL, ' ');
		shell->cmd[c].save = shell->cmd[c].token;
		shell->cmd[c].fd_in = -1;
		shell->cmd[c].fd_out = -1;
		ft_parse_heredoc(shell, shell->cmd[c].token);
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
		ft_exit(shell, "Error: malloc failed\n");
	shell->cmd[0].buffer = ft_trim_token(ft_strtok(shell->buffer, '|'), ' ');
	while (++i < shell->nb_cmd)
	{
		shell->cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' ');
	}
	ft_parse_token(shell);
	return (1);
}