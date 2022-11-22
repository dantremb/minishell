/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:05:32 by dantremb          #+#    #+#             */
/*   Updated: 2022/11/22 10:42:10 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**g_env;

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
	if (cmd_path != NULL)
		execve(cmd_path, shell->cmd[nb].token, g_env);
	write(2, shell->cmd[nb].token[0], ft_strlen(shell->cmd[nb].token[0]));
	write(2, ": command not found\n", 20);
	ft_free(cmd_path);
	ft_clear_fd();
	exit(127);
}
