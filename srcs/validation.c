/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 00:46:12 by dantremb          #+#    #+#             */
/*   Updated: 2022/12/07 12:12:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**g_env;

int	ft_open(t_cmd *cmd, char *str, int i)
{
	int	fd;

	while (str && (str[0] == '>' || str[0] == '<'))
		str++;
	if (i == 1)
		fd = open(str, O_RDONLY, 0644);
	else if (i == 2)
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 3)
		fd = open(str, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: open() error\n", 2);
		cmd->open_error = 1;
	}
	return (fd);
}

void	ft_export_error(t_shell *shell)
{
	char	*status;
	char	*export_status;

	status = ft_itoa(shell->error);
	export_status = ft_strjoin("?=", status, 0);
	ft_export(shell, export_status, 0);
	free (export_status);
	free (status);
}

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
	if (!shell->buffer)
		ft_exit(shell, "Goodbye!\n", 0);
	if (ft_is_only(shell->buffer, ' '))
	{
		shell->error = 127;
		return (0);
	}
	add_history(shell->buffer);
	if (ft_check_closed_quote(shell->buffer)
		|| ft_pipe_check(shell->buffer) || ft_empty_token(shell->buffer))
	{
		shell->error = 127;
		return (0);
	}
	return (1);
}
