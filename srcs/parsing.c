/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 01:18:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/18 22:47:12 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
extern t_data data;

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

	expand = ft_strjoin("<", data.heredoc, 0); // add < to heredoc variable *
	expand = ft_strjoin(expand, "=", 1); // add = after <*
	temps = ft_strjoin(expand, heredoc, 0);// add the name after <*=<*
	free(heredoc);
	ft_export(temps); // export <*=<* to env
	free(temps);
	expand[ft_strlen(expand) - 1] = '\0'; // remove = from <*=
	temps = ft_get_variable(expand); // get back the value of <*
	free(expand);
	data.heredoc[0] = data.heredoc[0] + 1; // increment heredoc variable for next heredoc
	return (temps); // return the value of <*= in a pointer not remalloc
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
				str = ft_expand_heredoc(ft_strjoin("<", data.heredoc, 0)); // create variable for heredoc
				ft_make_heredoc(token[i + 1], str); // create the file
				token[i][1] = '\0'; // replace << by <
				token[i + 1] = str + 1; // replace the next token by the filename
			}
			else // if the delimiter is on the next token
			{
				str = ft_expand_heredoc(ft_strjoin("<", data.heredoc, 0)); // create variable for heredoc
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
	data.cmd = ft_calloc(sizeof(t_cmd), data.cmd_count + 2); // allocate memory for the number of pipe
	if (data.cmd == NULL)
		ft_exit("Malloc error\n", 2);
	data.cmd[0].buffer = ft_trim_token(ft_strtok(data.buffer, '|'), ' '); // get the first token
	while (++i < data.cmd_count)// until strtok return NULL
		data.cmd[i].buffer = ft_trim_token(ft_strtok(NULL, '|'), ' '); // get the next token
	ft_parse_token(); // make token for each cmd
}