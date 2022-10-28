/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 00:46:12 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/27 21:00:09 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_error_status;

static int	ft_pipe_check(char *buf)
{
	char	*tmp;

	tmp = buf;
	if (buf[0] == '|' || buf[ft_strlen(buf) - 1] == '|')
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		return (1);
	}
	while (*tmp)
	{
		if (*tmp == '|' && *(tmp + 1) == '|')
		{
			*tmp = '\0';
			return (0);
		}
		if (*tmp == '|' && ft_is_only(tmp + 1, ' '))
		{
			ft_putstr_fd("minishell: syntax error\n", 2);
			return (1);
		}
		tmp++;
	}
	return (0);
}

static int	ft_check_closed_quote(char *buf)
{
	char	*tmp;

	tmp = buf;
	while (*tmp)
	{
		if (*tmp == '\'' || *tmp == '\"')
		{
			if (ft_strchr(tmp + 1, *tmp) == NULL)
			{
				printf("Error Quote not closed\n");
				return (1);
			}
			else
				tmp = ft_strchr(tmp + 1, *tmp);
		}
		tmp++;
	}
	return (0);
}

static int	ft_status(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->buffer[i] && (shell->buffer[i] == ' '))
		i++;
	if (shell->buffer[i] == '$' && shell->buffer[i + 1] == '?')
	{
		printf("Minishell: %d: command not found\n", g_error_status);
		printf("quoiuquoiqouqoiqoiqoiq\n");
		g_error_status = 127;
		return (1);
	}
	return (0);
}

static int	ft_empty_token(char *buf)
{
	char	*tmp;
	char	*token;
	int		i;

	i = 0;
	tmp = ft_strdup(buf);
	token = ft_strtok(tmp, '|');
	while (token)
	{
		if (ft_is_only(token, ' '))
		{
			printf("parse error near `|'\n");
			ft_free(tmp);
			return (1);
		}
		i++;
		token = (ft_strtok(NULL, '|'));
	}
	ft_free(tmp);
	return (0);
}

int	ft_buffer_integrity(t_shell *shell)
{
	if (ft_status(shell))
		return (0);
	if (ft_check_closed_quote(shell->buffer))
		return (0);
	if (ft_pipe_check(shell->buffer))
		return (0);
	if (ft_empty_token(shell->buffer))
		return (0);
	return (1);
}
