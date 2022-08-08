/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/08 14:03:53 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char **environ;
t_env	variable;

bool	ft_init_environement(void)
{
	printf("%s\n", "Init environment");
	variable.user = getenv("USER");
	if (variable.user == NULL)
		variable.user = ft_strdup("guest");
	variable.path = getenv("PATH");
	variable.pwd = getenv("PWD");
	if (variable.pwd == NULL)
		variable.pwd = ft_strdup("we do not know where we are");
	variable.name = getenv("NAME");
	if (variable.name == NULL)
		variable.name = ft_strdup("minishell");
	variable.nb_cmd = 0;
	variable.cmds = NULL;
	if (!variable.user || !variable.path)
		return (false);
	printf("User = %s\n", variable.user);
	printf("Pwd = %s\n", variable.pwd);
	//printf("Path = %s\n", variable.path);
	printf("Name = %s\n", variable.name);
	return (true);
}

void	ft_print_command_table(void)
{
	printf("here my command table\n");
}

void	ft_free_command_table(char	**t_cmd)
{
	int i;

	i = 0;
	while (t_cmd[i])
	{
		free(t_cmd[i]);
		i++;
	}
	free(t_cmd);
}

int	ft_number_of_command(char *buffer)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '|')
			count++;
		i++;
	}
	return (count);
}

bool	ft_execute_command_table(void)
{
	if (variable.nb_cmd == 0)
	{
		printf("Nothing to execute\n");
		return (false);
	}
	printf("execute the table with = ");
	ft_print_command_table();
	return (true);
}

bool	ft_parse_command(void)
{
	if (variable.nb_cmd == 0)
	{
		printf("Nothing to parse\n");
		return (false);
	}
	printf("parsing\n");
	return (true);
}

bool	ft_is_only_space(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

char	*ft_get_prompt(void)
{
	char *prompt;
	//green + user + @ + host + : + green + pwd + > + white
	prompt = ft_strjoin("\033[0;32m", variable.user, 0);
	prompt = ft_strjoin(prompt, "@", 1);
	prompt = ft_strjoin(prompt, variable.name, 1);
	prompt = ft_strjoin(prompt, ": ", 1);
	prompt = ft_strjoin(prompt, "\033[0;34m", 1);
	prompt = ft_strjoin(prompt, ft_get_pwd(), 1);
	prompt = ft_strjoin(prompt, "> ", 1);
	prompt = ft_strjoin(prompt, "\033[0m", 1);
	return (prompt);
}

int	main(int ac, char **argv, char **env)
{
	char	*buffer;
	(void)ac;
	(void)argv;
	(void)env;
	while (*environ)
	{
		printf("%s\n", environ[0]);
		environ++;
	}
	ft_init_environement();
	while (1)
	{
		buffer = readline(ft_get_prompt());
		if (ft_is_only_space(buffer))// if buffer is empty
			continue ;
		else if (ft_strncmp(buffer, "exit ", 4) == 0)// exit program
		{
			free (buffer);// free buffer
			exit (0);//	exit program
		}
		else
		{
			ft_parse_command();// parsing the buffer into the command table
			ft_execute_command_table();// executing the command table
			//ft_free_command_table(buffer);// free the command table
		}
	}
}
