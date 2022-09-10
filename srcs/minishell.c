/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/08 17:22:45 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
t_data data;

/* ************************MINISHELL UTILS************************************ */

void ft_free_table(void)
{
	int i;

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

void	ft_init_environement(char **env)
{
	int		i;

	data.expand[0] = 'a';
	data.expand[1] = '\0';
	data.heredoc[0] = 'a';
	data.heredoc[1] = '\0';
	data.buffer = NULL;
	data.prompt = NULL;
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

void	ft_print_table(void)
{
	int i;
	int j;
	
	i = 0;
	ft_color(RED);
	printf("---------- COMAND TABLE ----------\n");
	while (i < data.cmd_count)
	{
		j = 0;
		ft_color(CYAN);
		printf("[cmd %d]", i);
		while (data.cmd[i].token[j])
		{
			ft_color(YELLOW);
			printf("[%s]", data.cmd[i].token[j]);
			j++;
		}
		printf("\n");
		i++;
	}
	ft_color(RED);
	printf("---------------END----------------\n");
	ft_color(WHITE);
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

	prompt = ft_strjoin("\033[31;36m", ft_get_variable("USER") , 0);
	prompt = ft_strjoin(prompt, "@", 1);
	prompt = ft_strjoin(prompt, "Minishell", 1);
	prompt = ft_strjoin(prompt, ": ", 1);
	prompt = ft_strjoin(prompt, "\033[30;104m", 1);
	prompt = ft_strjoin(prompt, ft_get_variable("PWD"), 1);
	prompt = ft_strjoin(prompt, "> ", 1);
	prompt = ft_strjoin(prompt, "\033[0m", 1);
	return (prompt);
}

bool	ft_check_builtin(int nb)
{
	if (ft_strncmp(data.cmd[nb].token[0], "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(data.cmd[nb].token[0], "env", 3) == 0)
		return (true);
	else if (ft_strncmp(data.cmd[nb].token[0], "export", 6) == 0)
		return (true);
	else if (ft_strncmp(data.cmd[nb].token[0], "unset", 5) == 0)
		return (true);
	else if (ft_strncmp(data.cmd[nb].token[0], "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(data.cmd[nb].buffer, "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(data.cmd[nb].token[0], "exit", 4) == 0)
		return (true);
	else
		return (false);
	return (true);
}

/* ******************BUILT-IN************************************************ */

void	ft_cd(char *buffer)
{
	int new;
	int old;
	int ret;

	ret = chdir(buffer);
	old = -1;
	while (data.env[++old])
		if (ft_strncmp(data.env[old], "OLDPWD=", 7) == 0)
			break ;
	new = -1;
	while (data.env[++new])
		if (ft_strncmp(data.env[new], "PWD=", 4) == 0)
			break ;
	if (ret == 0)
	{
		free (data.env[old]);
		data.env[old] = ft_strjoin("OLDPWD=", data.env[new] + 4, 0);
		free (data.env[new]);
		data.env[new] = ft_strjoin("PWD=", getcwd(NULL, 0), 0);
	}
}

void	ft_env(void)
{
	int i;

	i = -1;
	while(data.env[++i])
		printf("%s\n", data.env[i]);
}

void	ft_unset(char *buffer)
{
	int	i;

	i = -1;
	while (data.env[++i])
	{
		if (ft_strncmp(data.env[i], buffer, ft_strlen(buffer)) == 0
			&& data.env[i][ft_strlen(buffer)] == '=')
		{
			free(data.env[i]);
			while (data.env[i + 1])
			{
				data.env[i] = data.env[i + 1];
				i++;
			}
			data.env[i] = NULL;
		}
	}
}

void	ft_echo(char **arg)
{
	int i;
	int flag;

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

void ft_export(char *arg)
{
	char	**temp;
	char	*duplicate;
	char	*var;
	int		i;

	if (ft_strchr(arg, '=') && arg[0] != '=')
	{
		duplicate = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
		var = ft_get_variable(duplicate);
		if (var)
			ft_unset(duplicate);
		free (duplicate);
		temp = ft_calloc(sizeof(char *), ft_array_size(data.env) + 2);
		if (temp == NULL)
			ft_exit("Malloc Error\n", 3);
		i = -1;
		while (data.env[++i])
			temp[i] = data.env[i];
		temp[i] = ft_strdup(arg);
		free(data.env);
		data.env = temp;
	}
	else if (arg == NULL)
		ft_env();

}

/* **************************PARSING***************************************** */

char	*ft_trim_token(char *buffer, char sep)
{
	int		i;
	if (!buffer)
		return (buffer);
	i = ft_strlen(buffer) - 1;
	while (buffer[i] == sep)
	{
		buffer[i] = '\0';
		i--;
	}
	while (*buffer == sep)
		buffer++;
	return (buffer);
}

int	ft_token_count(char *buffer, char sep)
{
	char *tmp;
	char *token;
	int i;
	
	i = 0;
	tmp = ft_strdup(buffer);
	token = ft_trim_token(ft_strtok(tmp, sep), ' ');
	while(token)
	{
		i++;
		token = ft_trim_token(ft_strtok(NULL, sep), ' ');
	}
	free(tmp);
	return (i);
}

char	*ft_remove_char(char *token, char sep)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == sep)
		{
			j = i;
			while (token[j])
			{
				token[j] = token[j + 1];
				j++;
			}
		}
		else
			i++;
	}
	return (token);
}

int	ft_open_fd(char *str, int i)
{
	static int	fd;

	if (i == 1)
		fd = open(str, O_RDONLY, 0644);
	else if (i == 2)
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 3)
		fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (i == 4)
		fd = open(str, O_RDWR | O_CREAT, 0644);
	else if (i == 5)
		fd = open(str, O_WRONLY | O_CREAT, 0644);
	if (!fd)
		return (-1);
	return (fd);
}

char	*ft_expand_token(char *token, int flag)
{
	char	*temp[4];

	temp[0] = ft_strchr(token, '$');
	temp[1] = ft_remove_char(ft_substr(token, 0, temp[0] - token), '\"');
	temp[2] = temp[0] + 1;
	while (++temp[0])
		if (*temp[0] == '\0' || *temp[0] == ' ' || *temp[0] == '$' || *temp[0] == '"' || *temp[0] == '\'')
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
		temp[0] = ft_expand_token(temp[0], 1);
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
			token = ft_expand_token(token + 1, 0);
		else
			token = ft_expand_token(token, 0);
		expand = ft_strjoin(data.expand, "-expand=", 0);
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

void	ft_heredoc(char *limiter, char *heredoc)
{
	char	*str;
	int		fd;
	int		i;

	fd = ft_open_fd(heredoc, 2);
	if (fd == -1)
	{
		printf("Error: heredoc file could not be opened\n");
		return ;
	}
	str = readline("<heredoc> ");
	i = 1;
	while (str)
	{
		if (ft_strnstr(str, limiter, ft_strlen(limiter)) != 0
			&& str[ft_strlen(limiter)] == '\0')
			break ;
		else if (i != 1)
			ft_putstr_fd("\n", fd);
		ft_putstr_fd(str, fd);
		free(str);
		str = readline("<heredoc> ");
		i = 0;
	}
	close(fd);
	free(str);
}

char	*ft_expand_heredoc(char *heredoc)
{
	char	*temps;
	char	*expand;

	expand = ft_strjoin(data.heredoc, "heredoc=", 0);
	temps = ft_strjoin(expand, heredoc, 0);
	free(heredoc);
	ft_export(temps);
	free(temps);
	expand[ft_strlen(expand) - 1] = '\0';
	heredoc = ft_get_variable(expand);
	free(expand);
	data.heredoc[0] = data.heredoc[0] + 1; 

	return (heredoc);
}

void	ft_check_redirect(char **token)
{
	int i;
	char	*str;

	i = -1;
	while (token[++i])
	{
		if (ft_strncmp(token[i], "<<\0", 3) == 0)
		{
			str = ft_expand_heredoc(ft_strjoin(&data.heredoc[0], "heredoc", 0));
			ft_heredoc(token[i + 1], str);
			token[i][1] = '\0';
			token[i + 1] = str;
		}
		else if (ft_strncmp(token[i], "<<", 2) == 0)
		{
			
			return;
		}
	}
}

void	ft_make_token(void)
{
	int c;
	int t;
	int count;

	c = -1;
	while (++c < data.cmd_count)
	{
		count = ft_token_count(data.cmd[c].buffer, ' ');
		data.cmd[c].token = ft_calloc(sizeof(char *), count + 2);
		t = 0;
		data.cmd[c].token[t] = ft_strtok(data.cmd[c].buffer, ' ');
		while (data.cmd[c].token[t])
		{
			t++;
			data.cmd[c].token[t] = ft_strtok(NULL, ' ');
		}
	}
	c = -1;
	while (++c < data.cmd_count)
		ft_check_redirect(data.cmd[c].token);
}

void 	ft_parse(void)
{
	int i;

	i = 0;
	data.cmd_count = ft_token_count(data.buffer, '|');
	data.cmd = ft_calloc(sizeof(t_cmd), data.cmd_count + 1);
	if (data.cmd == NULL)
		ft_exit("Malloc error\n", 2);
	data.cmd[0].buffer = ft_trim_token(ft_strtok(data.buffer, '|'), ' ');
	while (++i < data.cmd_count)
		data.cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' ');
	ft_make_token();
}

/* **********************ENGINE********************************************** */

char	*ft_get_path(char *buffer)
{
	char	*program;
	char	*env_path;
	char	**fcnt_path;
	char 	*test_path;
	int		i;
	i = 0;
	if (access(buffer, F_OK | X_OK) == 0)
		return (buffer);
	program = ft_strjoin("/", buffer, 0);
	env_path = ft_get_variable("PATH");
	if (env_path == NULL || program == NULL)
		return (NULL);
	fcnt_path = ft_split(env_path, ':');
	if (fcnt_path == NULL)
		return (NULL);
	while (fcnt_path[i])
	{
		test_path = ft_strjoin(fcnt_path[i], program, 0);
		if (access(test_path, F_OK | X_OK) == 0)
			break ;
		free (test_path);
		test_path = NULL;
		i++;
	}
	ft_free_array(fcnt_path);
	free(program);
	return (test_path);
}

void	ft_redirect_output_append(t_cmd *cmd)
{
	char	*str;

	str = ft_get_next_line(cmd->fd_out);
	while (str)
	{
		if (str)
			printf("%s", str);
		free(str);
		str = ft_get_next_line(cmd->fd_out);
	}
	free(str);
}

void	ft_find_redirect(int nb)
{
	int	i;

	i = -1;
	while (data.cmd[nb].token[++i])
	{
		if (ft_strncmp(data.cmd[nb].token[i], ">>", 2) == 0)
		{
			data.cmd[nb].fd_out = ft_open_fd(data.cmd[nb].token[++i], 4);
			ft_redirect_output_append(&data.cmd[nb]);
			dup2(data.cmd[nb].fd_out, STDOUT_FILENO);
			data.cmd[nb].token[--i] = NULL;
		}
		else if (ft_strncmp(data.cmd[nb].token[i], ">", 1) == 0)
		{
			data.cmd[nb].fd_out = ft_open_fd(data.cmd[nb].token[++i], 2);
			dup2(data.cmd[nb].fd_out, STDOUT_FILENO);
			data.cmd[nb].token[--i] = NULL;
		}
		else if (ft_strncmp(data.cmd[nb].token[i], "<", 1) == 0
			&& data.cmd[nb].token[i][1] != '<')
		{
			data.cmd[nb].fd_in = ft_open_fd(data.cmd[nb].token[++i], 1);
			dup2(data.cmd[nb].fd_in, STDIN_FILENO);
			if (data.cmd[nb].token[0][0] != '<')
				data.cmd[nb].token[--i] = NULL;
			else
			{
				data.cmd[nb].token++;
				data.cmd[nb].token++;
			}
		}
	}
	ft_clean_token(data.cmd[nb].token);
}

bool	ft_execute_builtin(int nb)
{
	if (ft_strncmp(data.cmd[nb].token[0], "echo", 4) == 0)
		ft_echo(data.cmd[nb].token);
	else if (ft_strncmp(data.cmd[nb].token[0], "env", 3) == 0)
		ft_env();
	else if (ft_strncmp(data.cmd[nb].token[0], "export", 6) == 0)
		ft_export(data.cmd[nb].token[1]);
	else if (ft_strncmp(data.cmd[nb].token[0], "unset\0", 6) == 0)
		ft_unset(data.cmd[nb].token[1]);
	else if (ft_strncmp(data.cmd[nb].token[0], "pwd", 3) == 0)
		printf("%s\n", ft_get_variable("PWD"));
	else if (ft_strncmp(data.cmd[nb].buffer, "cd", 2) == 0)
		ft_cd(data.cmd[nb].token[1]);
	else if (ft_strncmp(data.cmd[nb].token[0], "exit", 4) == 0)
		ft_exit("Goodbye\n", 3);
	else
		return (false);
	return (true);
}

void	ft_exec_cmd(char *cmd_path, int nb)
{
	
	if (execve(cmd_path, data.cmd[nb].token, data.env) == -1)
	{
		printf("minishell: %s: command not found\n", data.cmd[nb].token[0]);
		return ;
	}
}

void	ft_make_child_process(int nb)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		printf("Pipe failed\n");
		return ;
	}
	data.pid[nb] = fork();
	if (data.pid[nb] == -1)
	{
		printf("Fork failed\n");
		return ;
	}
	if (data.pid[nb] == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ft_find_redirect(nb);
		if (ft_execute_builtin(nb) == true)
			;
		else
			ft_exec_cmd(ft_get_path(data.cmd[nb].token[0]), nb);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

/* ***********************MAIN*********************************************** */

void	ft_fork_main(int nb)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_exit("Fork failed", 3);
	if (pid == 0)
	{
		ft_print_table();				//print the table with all the tokens
		while (++nb < data.cmd_count - 1)
			ft_make_child_process(nb);
		ft_find_redirect(nb);
		ft_print_table();
		if (ft_execute_builtin(nb) == true)
			;
		else
			ft_exec_cmd(ft_get_path(data.cmd[nb].token[0]), nb);
		nb = -1;
		while (++nb < data.cmd_count - 1)
			waitpid(data.pid[nb], NULL, 0);
		ft_exit("exit fork", 3);
	}
	else
		waitpid(pid, NULL, 0);
}

int	main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	int		i;

	i = -1;
	ft_init_environement(env);			// Copy environement variable in main struct
	while (1)
	{
		i = -1;
		data.prompt = ft_get_prompt();		// Get user and path for prompt
		data.buffer = readline(data.prompt);	// Fill the buffer with user input
		free(data.prompt);						// Free the prompt for next iteration
		add_history(data.buffer);
		if (ft_is_only(data.buffer, ' '))		// Newline on empty buffer
			free(data.buffer);
		else
		{
			ft_parse(); // tokenize the buffer
			if (ft_check_builtin(0) == 1 && data.cmd_count == 1)
			{
				ft_find_redirect(0);
				ft_execute_builtin(0);
			}
			else
				ft_fork_main(i);
			ft_free_table();
		}
	}
}
