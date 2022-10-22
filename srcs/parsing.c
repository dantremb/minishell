/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 01:18:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/21 23:29:47 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
extern t_data data;


void	ft_make_heredoc(char *limiter, char *heredoc)
{
	char	*str;
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		fd = ft_open_fd(heredoc, 2);
		if (fd == -1)
			ft_exit("Error: heredoc file not found", 1);
		while (1)
		{
			write(1, "<heredoc> ", 10);
			str = ft_get_next_line(0);
			if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0
				&& str[ft_strlen(limiter) + 1] == '\0')
				break ;
			ft_putstr_fd(str, fd);
			free(str);
		}
		close(fd);
		free(str);
		ft_exit(NULL, 3);
	}
	waitpid(pid, NULL, 0);
}


char	*ft_expand_heredoc(char *heredoc)
{
	char	*temps;
	char	*expand;

	expand = ft_strjoin("<", data.heredoc, 0);
	expand = ft_strjoin(expand, "=", 1);
	temps = ft_strjoin(expand, heredoc, 0);
	free(heredoc);
	ft_export(temps, 0);
	free(temps);
	expand[ft_strlen(expand) - 1] = '\0';
	temps = ft_get_variable(expand, 0);
	free(expand);
	data.heredoc[0] = data.heredoc[0] + 1;
	return (temps);
}

void	ft_parse_heredoc(char **token)
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
				str = ft_expand_heredoc(ft_strjoin("<", data.heredoc, 0));
				ft_make_heredoc(token[i + 1], str);
				token[i][1] = '\0';
				token[i + 1] = str + 1;
			}
			else
			{
				str = ft_expand_heredoc(ft_strjoin("<", data.heredoc, 0));
				ft_make_heredoc(&token[i][2], str);
				token[i] = str;
			}
		}
	}
}
