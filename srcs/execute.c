/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:05:32 by dantremb          #+#    #+#             */
/*   Updated: 2022/12/07 12:06:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**g_env;

static void	ft_clean_redirect(int *nb, char ***token, int *i,  int size)
{
	*nb = *nb - size;
	*token = *token + size;
	*i = -1;
}

void	ft_redirect(t_cmd *cmd, char *meta, int flag)
{
	int	i;

	i = -1;
	while (++i < cmd->nb_token)
	{
		if (ft_strncmp(cmd->token[i], meta, ft_strlen(meta)) == 0)
		{
			if (cmd->token[i][ft_strlen(meta)] == '\0')
			{
				cmd->fd = ft_open_fd(cmd->token[i + 1], flag);
				if (i == 0)
					ft_clean_redirect(&cmd->nb_token, &cmd->token, &i, 2);
				else
					cmd->token[i] = NULL;
			}
			else
			{
				cmd->fd = ft_open_fd(&cmd->token[i][0], flag);
				if (i == 0)
					ft_clean_redirect(&cmd->nb_token, &cmd->token, &i, 1);
				else
					cmd->token[i] = NULL;
			}
		}
	}
}

int	ft_find_redirect(t_shell *shell, int nb)
{
	ft_redirect(&shell->cmd[nb], ">>", 3);
	ft_redirect(&shell->cmd[nb], ">", 2);
	if (shell->cmd[nb].fd > 2)
	{
		dup2(shell->cmd[nb].fd, 1);
		shell->cmd[nb].fd = -1;
	}
	ft_redirect(&shell->cmd[nb], "<", 1);
	if (shell->cmd[nb].fd > 2)
	{
		dup2(shell->cmd[nb].fd, 0);
		shell->cmd[nb].fd = -1;
	}
	ft_clean_token(shell, shell->cmd[nb].token);
	if (shell->cmd[nb].open_error == 1)
	{
		dprintf(2, "return 1 after redirection\n");
		return (1);
	}
	return (0);
}

char	*ft_get_path(t_shell *shell, int nb)
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
	env_path = ft_get_variable("PATH", 0);
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
	if (cmd_path)
		execve(cmd_path, shell->cmd[nb].token, g_env);
	write(2, "minishell: ", 11);
	write(2, shell->cmd[nb].token[0], ft_strlen(shell->cmd[nb].token[0]));
	write(2, ": command not found\n", 20);
	ft_exit(shell, NULL, 1);
}
