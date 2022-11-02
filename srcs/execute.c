/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:05:32 by dantremb          #+#    #+#             */
/*   Updated: 2022/11/01 21:09:36 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redirect(t_cmd *cmd, char *meta, int side, int flag)
{
	int	i;
	int	fd;

	i = -1;
	fd = -1;
	while (++i < cmd->nb_token)
	{
		if (ft_strncmp(cmd->token[i], meta, ft_strlen(meta)) == 0)
		{
			if (cmd->token[i][ft_strlen(meta)] == '\0')
			{
				fd = ft_open_fd(cmd->token[i + 1], flag);
				if (fd > 2)
					dup2(fd, side);
				if (i == 0)
					cmd->token = cmd->token + 2;
				else
					cmd->token[i] = NULL;
			}
			else
			{
				fd = ft_open_fd(&cmd->token[i][0], flag);
				if (fd > 2)
					dup2(fd, side);
				if (i == 0)
					cmd->token = cmd->token + 1;
				else
					cmd->token[i] = NULL;
			}
		}
	}
}

void	ft_find_redirect(t_shell *shell, int nb)
{
	ft_redirect(&shell->cmd[nb], ">>", 1, 6);
	ft_redirect(&shell->cmd[nb], ">", 1, 2);
	ft_redirect(&shell->cmd[nb], "<", 0, 1);
	ft_clean_token(shell, shell->cmd[nb].token);
}

static char	*ft_get_path(t_shell *shell, int nb)
{
	char	*program;
	char	*env_path;
	char	**fcnt_path;
	char	*test_path;
	int		i;

	i = -1;
	if (access(shell->cmd[nb].token[0], F_OK | X_OK) == 0)
		return (shell->cmd[nb].token[0]);
	program = ft_strjoin("/", shell->cmd[nb].token[0], 0);
	env_path = ft_get_variable(shell, "PATH", 0);
	fcnt_path = ft_split(env_path, ':');
	if (program == NULL || env_path[0] == '\0' || fcnt_path == NULL)
		return (NULL);
	while (fcnt_path[++i])
	{
		test_path = ft_strjoin(fcnt_path[i], program, 0);
		if (access(test_path, F_OK | X_OK) == 0)
			break ;
		ft_free (test_path);
		test_path = NULL;
	}
	ft_free_array(fcnt_path);
	ft_free(program);
	return (test_path);
}

void	ft_execve(t_shell *shell, int nb)
{
	char	*cmd_path;

	cmd_path = ft_get_path(shell, nb);
	if (cmd_path != NULL)
		execve(cmd_path, shell->cmd[nb].token, shell->env);
	dprintf(2, "%s: command not found\n", shell->cmd[nb].token[0]);
	ft_free(cmd_path);
	exit(127);
}
