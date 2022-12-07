/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:05:32 by dantremb          #+#    #+#             */
/*   Updated: 2022/12/06 19:30:53 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**g_env;

int	ft_open(t_cmd *cmd, char *str, int i)
{
	static int	fd;

	while (str && (str[0] == '>' || str[0] == '<'))
		str++;
	dprintf(2, "open %s\n", str);
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
		return (-1);
	}
	return (fd);
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
				cmd->fd = ft_open(cmd, cmd->token[i + 1], flag);
				if (i == 0)
				{
					cmd->nb_token = cmd->nb_token - 2;
					cmd->token = cmd->token + 2;
					i = -1;
				}
				else
					cmd->token[i] = NULL;
			}
			else
			{
				cmd->fd = ft_open(cmd, &cmd->token[i][0], flag);
				if (i == 0)
				{
					cmd->nb_token = cmd->nb_token - 1;
					cmd->token = cmd->token + 1;
					i = -1;
				}
				else
					cmd->token[i] = NULL;
			}
		}
	}
}

void	ft_find_redirect(t_shell *shell, int nb)
{
	ft_print_table(shell);
	ft_redirect(&shell->cmd[nb], ">>", 3);
	ft_print_table(shell);
	ft_redirect(&shell->cmd[nb], ">", 2);
	ft_print_table(shell);
	if (shell->cmd[nb].fd > 2)
	{
		dup2(shell->cmd[nb].fd, 1);
		shell->cmd[nb].fd = -1;
	}
	ft_redirect(&shell->cmd[nb], "<", 1);
	ft_print_table(shell);
	if (shell->cmd[nb].fd > 2)
	{
		dup2(shell->cmd[nb].fd, 0);
		shell->cmd[nb].fd = -1;
	}
	ft_clean_token(shell, shell->cmd[nb].token);
	ft_print_table(shell);
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
