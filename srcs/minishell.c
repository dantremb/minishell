/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/22 00:21:41 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
t_data data;

void	ft_free_table(void)
{
	int	i;

	i = -1;
	while (++i < data.cmd_count)
		free(data.cmd[i].token);
	free(data.cmd);
	free(data.buffer);
}

void	ft_exit(char *str, int s)
{
	if (s <= 0)
		ft_putstr_fd(str, 2);
	if (s <= 1)
		free(data.buffer);
	if (s <= 2)
		ft_free_array(data.env);
	if (s <= 3)
		ft_free_table();
	exit(0);
}

void	ft_print_table(void)
{
	int	i;
	int	j;

	i = 0;
	while (i < data.cmd_count)
	{
		j = 0;
		ft_color(1);
		printf("------------ TOKEN -----------------\n");
		ft_color(6);
		printf("cmd %d = \t", i);
		while (data.cmd[i].token[j])
		{
			ft_color(3);
			printf("[\033[1;34m%s\033[1;33m]", data.cmd[i].token[j]);
			j++;
		}
		printf("\n");
		printf("------------ COMAND TABLE ----------\n");
		ft_color(6);
		printf("fd_in = \t");
		ft_color(3);
		printf("[\033[1;34m%d\033[1;33m]\n", data.cmd[i].fd_in);
		ft_color(6);
		printf("fd_out = \t");
		ft_color(3);
		printf("[\033[1;34m%d\033[1;33m]\n", data.cmd[i].fd_out);
		ft_color(1);
		i++;
	}
		printf("------------------------------------\n");
	ft_color(0);
}

char	*ft_get_variable(char *buffer)
{
	int		i;

	i = -1;
	while (data.env[++i])
	{
		if (ft_strncmp(data.env[i], buffer, ft_strlen(buffer)) == 0)
		{
			if (data.env[i][ft_strlen(buffer)] == '=')
				return (data.env[i] + (ft_strlen(buffer) + 1));
		}
	}
	buffer[0] = '\0';
	return (buffer);
}

char	*ft_get_prompt(void)
{
	char	*prompt;

	prompt = ft_strjoin("\033[0;32m", ft_get_variable("USER"), 0);
	prompt = ft_strjoin(prompt, "@", 1);
	prompt = ft_strjoin(prompt, "minishell", 1);
	prompt = ft_strjoin(prompt, ": ", 1);
	prompt = ft_strjoin(prompt, "\033[0;33m", 1);
	prompt = ft_strjoin(prompt, ft_get_variable("PWD"), 1);
	prompt = ft_strjoin(prompt, "> ", 1);
	prompt = ft_strjoin(prompt, "\033[0m", 1);
	return (prompt);
}

void	ft_init_environement(char **env, int ac, char **argv)
{
	int i;
	(void)ac;
	(void)argv;
	
	data.expand[0] = 'a';
	data.expand[1] = '\0';
	data.heredoc[0] = 'a';
	data.heredoc[1] = '\0';
	data.buffer = NULL;
	data.cmd_count = 0;
	data.cmd = NULL;
	i = 0;
	data.env = ft_calloc(sizeof(char *), ft_array_size(env));
	if (data.env == NULL)
		ft_exit("Malloc Error\n", 0);
	while (env[i])
	{
		data.env[i] = ft_strdup(env[i]);
		if (!data.env[i])
			ft_exit("Malloc Error\n", 0);
		i++;
	}
}

char	*ft_get_path(int nb)
{
	char	*program;
	char	*env_path;
	char	**fcnt_path;
	char 	*test_path;
	int		i;
	i = -1;
	if (access(data.cmd[nb].token[0], F_OK | X_OK) == 0)
		return (data.cmd[nb].token[0]);
	program = ft_strjoin("/", data.cmd[nb].token[0], 0);
	env_path = ft_get_variable("PATH");
	fcnt_path = ft_split(env_path, ':');
	if (program == NULL || env_path == NULL || fcnt_path == NULL)
		return (NULL);
	while (fcnt_path[++i])
	{
		test_path = ft_strjoin(fcnt_path[i], program, 0);
		if (access(test_path, F_OK | X_OK) == 0)
			break ;
		free (test_path);
		test_path = NULL;
	}
	ft_free_array(fcnt_path);
	free(program);
	return (test_path);
}

char	*ft_expand(char *token, int flag)
{
	char	*temp[4];

	temp[0] = ft_strchr(token, '$');
	temp[1] = ft_remove_char(ft_substr(token, 0, temp[0] - token), '\"');
	temp[2] = temp[0] + 1;
	while (++temp[0])
		if (*temp[0] == '\0' || *temp[0] == ' ' || *temp[0] == '$'
			|| *temp[0] == '"' || *temp[0] == '\'')
			break ;
	temp[2] = ft_substr(temp[2] , 0, temp[0] - temp[2] );
	temp[3] = ft_get_variable(temp[2] );
	temp[3]  = ft_strjoin(temp[1], temp[3], 1);
	free (temp[2]);
	temp[1] = ft_remove_char(ft_substr(temp[0], 0, ft_strlen(temp[0])), '\"');
	temp[0] = ft_strjoin(temp[3] , temp[1], 1);
	free(temp[1]);
	if (flag == 1)
		free (token);
	if (ft_strchr(temp[0], '$'))
		temp[0] = ft_expand(temp[0], 1);
	return (temp[0]);
}

char	*ft_expand_variable(char *token)
{
	char	*temps;
	char	*expand;

	if (token[0] == '$' && ft_strchr(&token[1], '$') == NULL)
		token = ft_get_variable(&token[1]);
	else
	{
		if (token[0] == '\"')
			token = ft_expand(token + 1, 0);
		else
			token = ft_expand(token, 0);
		expand = ft_strjoin(&data.expand[0], "-expand=", 0);
		temps = ft_strjoin(expand, token, 0);
		free(token);
		ft_export(temps);
		free(temps);
		expand[ft_strlen(expand) - 1] = '\0';
		token = ft_get_variable(expand);
		free(expand);
		data.expand[0] = data.expand[0] + 1; 
	}
	return (token);
}

void	ft_clean_token(char **token)
{
	int t;

	t = 0;
	while (token[t])
	{
		if (token[t][0] == '\'' && token[t][ft_strlen(token[t]) - 1] == '\'')
			ft_remove_char(token[t], '\'');
		else if (token[t][0] == '\"' && token[t][ft_strlen(token[t]) - 1] == '\"')
		{
			if (ft_strchr(token[t], '$'))
				token[t] = ft_expand_variable(token[t]);
			else
				ft_remove_char(token[t], '\"');
		}
		else
		{
			token[t] = ft_trim_token(token[t], ' ');
			if (ft_strchr(token[t], '$'))
				token[t] = ft_expand_variable(token[t]);
		}
		t++;
	}
}

bool	ft_execute_builtin(int nb)
{
	if (ft_strncmp(data.cmd[nb].token[0], "echo", 4) == 0)
		ft_echo(data.cmd[nb].token);
	else if (ft_strncmp(data.cmd[nb].token[0], "env", 3) == 0)
		ft_env(1);
	else if (ft_strncmp(data.cmd[nb].token[0], "export", 6) == 0)
		ft_export(data.cmd[nb].token[1]);
	else if (ft_strncmp(data.cmd[nb].token[0], "unset\0", 6) == 0)
		ft_unset(data.cmd[nb].token[1]);
	else if (ft_strncmp(data.cmd[nb].token[0], "pwd\0", 4) == 0)
		printf("%s\n", ft_get_variable("PWD"));
	else if (ft_strncmp(data.cmd[nb].buffer, "cd", 2) == 0)
		ft_cd(data.cmd[nb].token[1]);
	else if (ft_strncmp(data.cmd[nb].token[0], "exit\0", 5) == 0)
		ft_exit("Goodbye\n", 3);
	else
		return (false);
	return (true);
}
void	ft_execve(int nb)
{
	char	*cmd_path;
	
	ft_clean_token(data.cmd[nb].token);
	if (ft_execute_builtin(nb) == false)
	{
		cmd_path = ft_get_path(nb);
		if (execve(cmd_path, data.cmd[nb].token, data.env))
			printf("%s: command not found\n", data.cmd[nb].token[0]);
	}
	exit(0);
}

void	ft_exec_cmd(int nb)
{
	int	fd[2];
	
	if(pipe(fd) == -1)
		ft_exit("pipe error\n", 3);
	data.cmd[nb].pid = fork();
	if (data.cmd[nb].pid == 0)
	{
		if (nb < data.cmd_count - 1)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
		}
		ft_execve(nb);
	}
	else if (nb < data.cmd_count - 1)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

void	ft_exec_cmd_solo(int nb)
{
	char *cmd_path;
	
	ft_clean_token(data.cmd[nb].token);
	if (ft_execute_builtin(nb) == false)
	{
		data.cmd[nb].pid = fork();
		if (data.cmd[nb].pid == 0)
		{
			cmd_path = ft_get_path(nb);
			if (execve(cmd_path, data.cmd[nb].token, data.env))
				printf("%s: command not found\n", data.cmd[nb].token[0]);
		}
		else
			waitpid(data.cmd[nb].pid, NULL, 0);
	}
}

void	ft_execute(int nb)
{
	int old_stdin;
	
	old_stdin = dup(STDIN_FILENO);
	while (nb < data.cmd_count) 
		ft_exec_cmd(nb++);
	nb = 0;
	while (nb < data.cmd_count)
		waitpid(data.cmd[nb++].pid, NULL, 0);
	dup2(old_stdin, STDIN_FILENO);
}

int	main(int ac, char **argv, char **env)
{
	char	*prompt;
	
	ft_init_environement(env, ac, argv);
	while (1)
	{
		prompt = ft_get_prompt();
		data.buffer = readline(prompt);
		free(prompt);
		if (ft_is_only(data.buffer, ' '))
			continue;
		else
		{
			add_history(data.buffer);
			ft_parse_cmd();
			ft_execute(0);
			ft_free_table();
		}
	}
}
