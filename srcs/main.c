/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main->c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student->42->fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:49:16 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/30 22:56:22 by dantremb         ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int error_status;

char	*ft_get_variable(shell_t *shell, char *buffer, int flag)
{
	int		i;

	i = -1;
	if (!buffer)
		return (NULL);
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], buffer, ft_strlen(buffer)) == 0)
		{
			if (shell->env[i][ft_strlen(buffer)] == '=')
				return (shell->env[i] + (ft_strlen(buffer) + 1));
		}
	}
	if (flag == 1)
		buffer[0] = '\0';
	return (buffer);
}

void	ft_echo(char **arg)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (arg[1] && ft_strncmp(arg[1], "-n\0", 3) == 0)
	{
		flag = 1;
		i++;
	}
	while (arg[i])
	{
		if (ft_is_only(arg[i], ' '))
			i++;
		else
		{
			printf("%s", arg[i++]);
			if (arg[i])
				printf(" ");
		}
	}
	if (flag == 0)
		printf("\n");
}

void	ft_env(shell_t *shell, int flag)
{
	int	i;

	i = -1;
	if (flag == 0)
	{
		while (shell->env[++i])
			printf("[%d]%s\n", i, shell->env[i]);
	}
	else
	{
		while (shell->env[++i])
		{
			if (shell->env[i][0] != '<' && shell->env[i][1] != '-' && ft_strchr(shell->env[i], '='))
				printf("%s\n", shell->env[i]);
		}
	}
}

void	ft_unset(shell_t *shell, char *buffer)
{
	int	i;

	i = -1;
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], buffer, ft_strlen(buffer)) == 0
			&& shell->env[i][ft_strlen(buffer)] == '=')
		{
			free(shell->env[i]);
			while (shell->env[i + 1])
			{
				shell->env[i] = shell->env[i + 1];
				i++;
			}
			shell->env[i] = NULL;
		}
	}
}

void	ft_export(shell_t *shell, char *arg, int flag)
{
	char	*duplicate;

	if (!arg)
		ft_env(shell, 0);
	else if (arg && ft_isalpha(arg[0]) == 0 && flag == 1)
		printf("-bash: export: `%s': not a valid identifier\n", arg);
	else
	{
		if (ft_strchr(arg, '='))
		{
			duplicate = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
			if (ft_get_variable(shell, duplicate, 0))
				ft_unset(shell, duplicate);
			free (duplicate);
		}
		shell->env = ft_remalloc(shell->env, 1, 1);
		shell->env[ft_array_size(shell->env)] = 
			ft_remove_char(ft_remove_char(ft_strdup(arg), '\''), '\"');
	}
}

void	ft_cd(shell_t *shell, char *buffer)
{
	char	*temp[2];
	
	if (buffer && chdir(buffer) == 0)
	{
		ft_unset(shell, "OLDPWD");
		temp[0] = ft_get_variable(shell, "PWD", 0);
		temp[1] = ft_strjoin("OLDPWD=", temp[0], 0);
		ft_export(shell, temp[1], 0);
		free(temp[1]);
		ft_unset(shell, "PWD");
		temp[0] = getcwd(NULL, 0);
		temp[1] = ft_strjoin("PWD=", temp[0], 0);
		ft_export(shell, temp[1], 0);
		free(temp[0]);
		free(temp[1]);
	}
	else
		printf("cd: %s: No such file or directory\n", buffer);
}

/*void	ft_redirect(t_cmd *cmd, char *meta, int side, int flag)
{
	int i;
	int fd;

	i = -1;
	while (cmd->token[++i])
	{
		if (ft_strncmp(cmd->token[i], meta, ft_strlen(meta)) == 0)
		{
			if (cmd->token[i][ft_strlen(meta)] == '\0')
			{
				fd = ft_open_fd(cmd->token[i + 1], flag);
				dup2(fd, side);
				if (i == 0)
					cmd->token = cmd->token + 2;
				else
					cmd->token[i] = NULL;
			}
			else
			{
				fd = ft_open_fd(&cmd->token[i][ft_strlen(meta)], flag);
				dup2(fd, side);
				if (i == 0)
					cmd->token = cmd->token + 1;
				else
					cmd->token[i] = NULL;
			}
		}
	}
}*/

bool	ft_execute_builtin(shell_t *shell, int nb)
{
	if (ft_strncmp(shell->cmd[nb].token[0], "echo", 4) == 0)
		ft_echo(shell->cmd[nb].token);
	else if (ft_strncmp(shell->cmd[nb].token[0], "env", 3) == 0)
		ft_env(shell, 1);
	else if (ft_strncmp(shell->cmd[nb].token[0], "export", 6) == 0)
		ft_export(shell, shell->cmd[nb].token[1], 1);
	else if (ft_strncmp(shell->cmd[nb].token[0], "unset\0", 6) == 0)
		ft_unset(shell->cmd[nb].token[1]);
	else if (ft_strncmp(shell->cmd[nb].token[0], "pwd\0", 4) == 0)
		printf("%s\n", ft_get_variable("PWD", 0));
	else if (ft_strncmp(shell->cmd[nb].buffer, "cd", 2) == 0)
		ft_cd(shell->cmd[nb].token[1]);
	else if (ft_strncmp(shell->cmd[nb].token[0], "exit\0", 5) == 0)
		ft_exit("Goodbye\n", 3);
	else
		return (false);
	return (true);
}

void	ft_execve(shell_t *shell, int nb)
{
	char	*cmd_path;
	int		status;
	
	//ft_redirect(&shell->cmd[nb], ">>", 1, 6);
	//ft_redirect(&shell->cmd[nb], ">", 1, 2);
	//ft_redirect(&shell->cmd[nb], "<", 0, 1);
	ft_clean_token(shell->cmd[nb].token);
	if (ft_execute_builtin(nb) == false)
	{
		cmd_path = ft_get_path(nb);
		status = execve(cmd_path, shell->cmd[nb].token, shell->env);
		dprintf(2, "%s: command not found\n", shell->cmd[nb].token[0]);
	}
	exit(status);
}

void	ft_exec_cmd(shell_t *shell, int nb)
{
	int	fd[2];
	
	if(pipe(fd) == -1)
		ft_exit("pipe error\n", 3);
	shell->cmd[nb].pid = fork();
	if (shell->cmd[nb].pid == 0)
	{
		if (nb < shell->cmd_count - 1)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
		}
		ft_execve(nb);
	}
	else if (nb < shell->cmd_count - 1)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

void	ft_execute_solo(shell_t *shell, int nb)
{
	int	status;
	
	ft_redirect(&shell->cmd[nb], ">>", 1, 6);
	ft_redirect(&shell->cmd[nb], ">", 1, 2);
	ft_redirect(&shell->cmd[nb], "<", 0, 1);
	ft_clean_token(shell->cmd[nb].token);
	if (ft_execute_builtin(shell, nb) == false)
	{
		shell->cmd[nb]->pid = fork();
		if (shell->pid[nb] == 0)
			ft_execve(shell, nb);
		else
			waitpid(shell->pid[nb], &status, 0);
		if (status > 256)
			error_status = 127;
		else if (status == 256)
			error_status = 1;
		else
			error_status = 0;
	}
}

void	ft_execute_cmd(shell_t *shell, int nb)
{
	int old_stdin;
	int old_stdout;
	int	status;

	old_stdin = dup(STDIN_FILENO);
	old_stdout = dup(STDOUT_FILENO);
	if (shell->nb_cmd > 1){
		while (nb < shell->nb_cmd) 
			ft_exec_cmd(shell, nb++);
		nb = 0;
		while (nb < shell->nb_cmd)
			waitpid(shell->cmd[nb++].pid, &status, 0);
		if (status > 256)
			error_status = 127;
		else if (status == 256)
			error_status = 1;
		else
			error_status = 0;
	}
	else {
		ft_execute_solo(shell, nb);
	}
	dup2(old_stdin, STDIN_FILENO);
	dup2(old_stdout, STDOUT_FILENO);
}

int	main(int ac, char **av, char **env)
{

	shell_t *shell;
	
	shell = ft_init_minishell(ac, av, env);
	signal(SIGINT, ft_signal);
	ft_getprompt(shell);
	ft_exit(shell, "Goodbye\n", 0, 2);
}

/***environement***/

shell_t	*ft_init_minishell(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	shell_t *shell;

	error_status = 0;
	shell = ft_calloc(1, sizeof(shell_t));
	if (!shell)
		ft_putstr_fd("Error: malloc failed\n", 2);
	shell->env = ft_remalloc(env, 0, 0);
	if (shell->env == NULL){
		free(shell);
		ft_putstr_fd("Error: malloc failed\n", 2);
	}
	return (shell);
}

/***parsing***/

int	ft_status(shell_t *shell)
{
	int	i;

	i = 0;
	while (shell->buffer[i] && (shell->buffer[i] == ' ' || shell->buffer[i] == '\t'))
		i++;
	if (shell->buffer[i] == '$' && shell->buffer[i + 1] == '?')
	{
		printf("%d: command not found\n", error_status);
		error_status = 0;
		return (1);
	}
	return (0);
}

int	ft_check_closed_quote(char *buf)
{
	int	i;
	int	d;
	int	s;

	i = -1;
	d = 0;
	s = 0;
	while (buf[++i]){
		if (buf[i] == '\"')
			d++;
		if (buf[i] == '\'')
			s++;
	}
	if ((d && (d % 2) != 0) || (s && (s % 2)) != 0){
		printf("Error Quote not closed\n");
		return (0);
	}
	return (1);
}

int 	ft_parse(shell_t *shell)
{
	int i;

	i = 0;
	if (ft_check_closed_quote(shell->buffer) == 0 || ft_status(shell))
		return (0);
	shell->nb_cmd = ft_token_count(shell->buffer, '|');
	shell->cmd = ft_calloc(sizeof(t_cmd), shell->nb_cmd);
	if (shell->cmd == NULL)
		ft_exit(shell, "Error: malloc failed\n", 15, 3);
	shell->cmd[0].buffer = ft_trim_token(ft_strtok(shell->buffer, '|'), ' ');
	while (++i < shell->nb_cmd)
		shell->cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' ');
	//ft_parse_token();
	return (1);
}

/***get prompt***/

int	ft_getprompt(shell_t *shell)
{
	shell->buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
	while (shell->buffer != NULL)
	{
		if (!ft_is_only(shell->buffer, ' '))
		{
			add_history(shell->buffer);
			if (ft_parse(shell)){
				ft_execute_cmd(shell, 0);
				ft_free(shell, 8);
			}
			else
				ft_free(shell, 9);
		}
		shell->buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
	}
	return (0);
}

/***exit and free***/

void	ft_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		error_status = 130;
	}
}

void	ft_free(shell_t *shell, int flag)
{
	if (flag == 1)
		free(shell);
	if (flag <= 2)
		ft_free_array(shell->env);
	if (flag >= 8)
		free(shell->cmd);
	if (flag == 9)
		free(shell->buffer);
}

void	ft_exit(shell_t *shell, char *msg, int status, int flag)
{
	ft_putstr_fd(msg, 2);
	ft_free(shell, flag);
	exit(status);
}
