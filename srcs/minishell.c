/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/12 00:29:14 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
t_data data;

/* **********************MINISHELL UTILS************************************* */

void	ft_free_table(void)
{
	int	i;

	i = -1;
	while (++i < data.cmd_count)
		free(data.cmd[i].token);
	free(data.cmd);
	free(data.pid);
	free(data.buffer);
}

void	ft_exit(char *str, int s)
{
	if (s <= 0)
		ft_putstr_fd(str, 2);
	if (s <= 1)
		free(data.buffer);
	if (s <= 2)
	{
		ft_free_array(data.env);
		free(data.pid);
	}
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
	prompt = ft_strjoin(prompt, "Minishell", 1);
	prompt = ft_strjoin(prompt, ": ", 1);
	prompt = ft_strjoin(prompt, "\033[0;34m", 1);
	prompt = ft_strjoin(prompt, ft_get_variable("PWD"), 1);
	prompt = ft_strjoin(prompt, "> ", 1);
	prompt = ft_strjoin(prompt, "\033[0m", 1);
	return (prompt);
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

void	ft_init_environement(char **env)
{
	int i;

	data.expand[0] = 'a';
	data.expand[1] = '\0';
	data.heredoc= 'a';
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

/* **********************BUILT-IN******************************************** */

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

void	ft_env(void)
{
	int	i;

	i = -1;
	while (data.env[++i])
		printf("%s\n", data.env[i]);
}

void	ft_cd(char *buffer)
{
	int	new;
	int	old;
	int	ret;

	ret = chdir(buffer);
	old = -1;
	while (data.env[++old])
	{
		if (ft_strncmp(data.env[old], "OLDPWD=", 7) == 0)
			break ;
	}
	new = -1;
	while (data.env[++new])
	{
		if (ft_strncmp(data.env[new], "PWD=", 4) == 0)
			break ;
	}
	if (ret == 0)
	{
		free (data.env[old]);
		data.env[old] = data.env[new];
		data.env[new] = ft_strjoin("PWD=", getcwd(NULL, 0), 0);
	}
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

void	ft_export(char *arg)
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

/* **********************PARSING********************************************* */

// ft_heredoc(char *limiter, char *heredoc) make a child process to make the heredoc
void	ft_make_heredoc(char *limiter, char *heredoc)
{
	char	*str;
	int		fd;
	pid_t	pid;

	pid = fork(); // make a child process
	if (pid == 0) // if i'm the child
	{
		fd = ft_open_fd(heredoc, 2); // open file
		if (fd == -1)
			ft_exit("Error: heredoc file not found", 1);
		while (1)
		{
			write(1, "<heredoc> ", 10); // print prompt
			str = ft_get_next_line(0); // get line
			if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0 //if str if NULL
				&& str[ft_strlen(limiter) + 1] == '\0') // or if the line is the limiter
				break ; // break the loop
			ft_putstr_fd(str, fd); // write the line in the file
			free(str); // free the line
		}
		close(fd); // close the file
		free(str); // free the line
		ft_exit(NULL, 3); // exit the child
	}
	waitpid(pid, NULL, 0); // wait the child to finish de heredoc
}

// ft_expand_heredoc(char *heredoc) will create a variable in environnement with the heredoc name
char	*ft_expand_heredoc(char *heredoc)
{
	char	*temps;
	char	*expand;

	expand = ft_strjoin("<", &data.heredoc, 0); // add < to heredoc variable *
	expand = ft_strjoin(expand, "=", 1); // add = after <*
	temps = ft_strjoin(expand, heredoc, 0);// add the name after <*=<*
	free(heredoc);
	ft_export(temps); // export <*=<* to env
	free(temps);
	expand[ft_strlen(expand) - 1] = '\0'; // remove = from <*=
	heredoc = ft_get_variable(expand); // get back the value of <*
	free(expand);
	data.heredoc = data.heredoc + 1; // increment heredoc variable for next heredoc
	return (heredoc); // return the value of <*= in a pointer not remalloc
}

// ft_parse_heredoc(char **token) will replace heredoc with a infile redirection on the file created by ft_heredoc
void	ft_parse_heredoc(char **token)
{
	int i;
	char	*str;

	i = -1;
	while (token[++i]) // scan all token
	{
		if (ft_strncmp(token[i], "<<", 2) == 0) //if the 2 first char is "<<"
		{
			if (token[i][2] == '\0') // if its only << in token
			{
				//if next token do not exist cancel the job
				str = ft_expand_heredoc(ft_strjoin("<", &data.heredoc, 0)); // create variable for heredoc
				ft_make_heredoc(token[i + 1], str); // create the file
				token[i][1] = '\0'; // replace << by <
				token[i + 1] = str + 1; // replace the next token by the filename
			}
			else // if the delimiter is on the next token
			{
				str = ft_expand_heredoc(ft_strjoin("<", &data.heredoc, 0)); // create variable for heredoc
				ft_make_heredoc(&token[i][2], str); // create the file
				token[i] = str; // replace the token by the filename
			}
		}
	}
}

// ft_parse_token(void) will split the individual buffer into a token list to be trim and expand
void	ft_parse_token(void)
{
	int c;
	int t;
	int count;

	c = -1;
	while (++c < data.cmd_count) // for each command
	{
		data.cmd[c].fd_in = 0;
		data.cmd[c].fd_out = 1;
		count = ft_token_count(data.cmd[c].buffer, ' '); // count the number of token
		data.cmd[c].token = ft_calloc(sizeof(char *), count + 2); // allocate memory for the token list
		t = 0;
		data.cmd[c].token[t] = ft_strtok(data.cmd[c].buffer, ' '); // get the first token
		while (data.cmd[c].token[t++])// until strtok return NULL
			data.cmd[c].token[t] = ft_strtok(NULL, ' '); // get the next token
		ft_parse_heredoc(data.cmd[c].token); // check token list for heredoc
	}
}

// ft_parse_cmd(void) will split the readline buffer into smaller buffer for each command
void 	ft_parse_cmd(void)
{
	int i;

	i = 0;
	data.cmd_count = ft_token_count(data.buffer, '|'); // count the number of pipe
	data.cmd = ft_calloc(sizeof(t_cmd), data.cmd_count + 1); // allocate memory for the number of pipe
	data.pid = ft_calloc(sizeof(pid_t), data.cmd_count - 1); // allocate memory for PID table
	if (data.cmd == NULL || data.pid == NULL)
		ft_exit("Malloc error\n", 2);
	data.cmd[0].buffer = ft_trim_token(ft_strtok(data.buffer, '|'), ' '); // get the first token
	while (++i < data.cmd_count)// until strtok return NULL
		data.cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' '); // get the next token
	ft_parse_token(); // make token for each cmd
}

/* **********************ENGINE********************************************** */

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


void	ft_redirect(t_cmd *cmd, char *meta, int size, int flag)
{
	int i;
	int fd;

	i = -1;
	while (cmd->token[++i])
	{
		if (ft_strncmp(cmd->token[i], meta, size) == 0)
		{
			if (cmd->token[i][size] == '\0')
			{
				fd = ft_open_fd(cmd->token[i + 1], flag);
				dprintf(2, "fd open 1tok = %d\n", fd);
				if (i == 0)
					cmd->token = cmd->token + 2;
				else
					cmd->token[i] = NULL;
			}
			else
			{
				fd = ft_open_fd(&cmd->token[i][size], flag);
				dprintf(2, "fd open 2tok = %d\n", fd);
				if (i == 0)
					cmd->token = cmd->token + 1;
				else
					cmd->token[i] = NULL;
			}
			if (meta[0] == '<')
			{
				cmd->fd_in = fd;
				dprintf(2, "redirect in %d\n", cmd->fd_in);
				dup2(cmd->fd_in, 0);
			}
			else
			{
				cmd->fd_out = fd;
				dprintf(2, "redirect out %d\n", cmd->fd_out);
				dup2(cmd->fd_out, 1);
			} 
		}
	}
}

void	ft_exec_cmd(char *cmd_path, int nb)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		ft_redirect(&data.cmd[nb], ">>", 2, 6);
		ft_redirect(&data.cmd[nb], ">", 1, 2);
		ft_redirect(&data.cmd[nb], "<", 1, 1);
		execve(cmd_path, data.cmd[nb].token, data.env);
	}
	waitpid(pid, NULL, 0);
}

void	ft_execute(int nb)
{
	if (ft_execute_builtin(nb) == false)
		ft_exec_cmd(ft_get_path(nb), nb);
}

/* **********************MAIN************************************************ */

int	main(int ac, char **argv, char **env)
{
	(void)ac;
	(void)argv;
	//int		i;

	ft_init_environement(env); // Copy environement variable in main struct
	while (1)
	{
		//i = -1;
		data.prompt = ft_get_prompt(); // Get user and current folder path for prompt
		data.buffer = readline(data.prompt); // Fill the buffer with user input
		free(data.prompt); // Free the prompt for next iteration
		if (ft_is_only(data.buffer, ' ')) // Newline on empty buffer
			continue;
		else
		{
			add_history(data.buffer);
			ft_parse_cmd(); // tokenize the buffer
			ft_print_table(); //print the table with all the tokens
			if (data.cmd_count == 1) // If there is only one command
				ft_execute(0); // Execute the command
			ft_print_table();
			ft_free_table();
		}
	}
}
