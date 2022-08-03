/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/06/22 19:55:28 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_path(char **envp)
{
	char	*envp_path;
	char	**fnct_path;
	int		i;

	envp_path = NULL;
	fnct_path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])))
		{
			envp_path = ft_strdup(envp[i]);
			if (!envp_path)
				return (NULL);
			break ;
		}
		i++;
	}
	if (!envp_path)
		return (NULL);
	fnct_path = ft_split(envp_path, 58);
	free(envp_path);
	return (fnct_path);
}

char	*get_cmd_path(char **envp, char *cmd)
{
char	**fcnt_path;
	char	*test_path;
	int		i;

	i = 0;
	if (access(cmd + 1, F_OK | X_OK) == 0)
		return (cmd + 1);
	fcnt_path = get_path(envp);
	while (fcnt_path[i])
	{
		test_path = ft_strjoin(fcnt_path[i], cmd);
		if (access(test_path, F_OK | X_OK) == 0)
			break ;
		free (test_path);
		i++;
	}
	i = -1;
	while (fcnt_path[++i])
		free(fcnt_path[i]);
	free(fcnt_path);
	return (test_path);
}

void	command(char *argv, char **envp)
{
	char	**options;
	char	*path;
	char	*cmd;
	int		i;

	options = ft_split(argv, 32);
	cmd = ft_strjoin("/", options[0]);
	path = get_cmd_path(envp, cmd);
	if (!path | !cmd | !options)
	{
		i = -1;
		while (options[++i])
			free (options[i]);
		free (options);
		free (cmd);
		return ;
	}
	dprintf(2, "path = %s option = %s + %s + %s\n", path, options[0], options[1], options[2]);
	i = execve(path, options, envp);
	dprintf(2, "after execve from %s\n", path);
	if (i == -1)
		return ;
}

void	child(char **argv, char **envp, int *fd)
{
	int		file1;

	file1 = open(argv[1], O_RDONLY, 0644);
	if (file1 == -1)
		return ;
	dup2(fd[1], STDOUT_FILENO);
	dup2(file1, STDIN_FILENO);
	close(fd[0]);
	command(argv[2], envp);
	close(file1);
}

void	parent(char **argv, char **envp, int *fd)
{
	int		file2;

	file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file2 == -1)
		return ;
	dup2(fd[0], STDIN_FILENO);
	dup2(file2, STDOUT_FILENO);
	close(fd[1]);
	command(argv[3], envp);
	close(file2);
}

int	ft_execute(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			return(-1);
		pid = fork();
		if (pid == -1)
			return(-1);
		else if (pid == 0)
			child(argv, envp, fd);
		waitpid(0, NULL, 0);
		parent(argv, envp, fd);
	}
	else
		ft_printf("Bad Argument\n");
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*buffer;
	int		i;

	while (1)
	{
		i = 0;
		buffer = readline("\033[0;32mMINISHELL->\033[0;37m");
		if (ft_strncmp(buffer, "env", 3) == 0)
		{
			while (env[++i])
				ft_printf("%s\n", env[i]);
		}
		else if (ft_strncmp(buffer, "exit", 4) == 0)
		{
			exit (0);
		}
		else if (ft_strncmp(buffer, "pipe", 4) == 0)
		{
			ft_execute(ac, av, env);
		}
		else
			dprintf(2, "\033[0;31mCommand not found\n\033[0;37m");
		free(buffer);
	}
}
