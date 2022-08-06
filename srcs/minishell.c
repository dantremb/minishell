/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/06 18:52:54 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	variable;

bool	ft_init_environement(void)
{
	printf("%s\n", "Init environment");
	variable.user = getenv("USER");
	variable.path = getenv("PATH");
	variable.nb_cmd = 0;
	variable.cmds = NULL;
	if (!variable.user || !variable.path)
		return (false);
	printf("User = %s\n", variable.user);
	printf("Path = %s\n", variable.path);
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

int	ft_number_of_command(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
			count++;
		i++;
	}
	return (count);
}

bool	ft_execute_command_table(char *buffer)
{
	printf("execute the table with = ");
	if (!buffer)
		return (false);
	ft_print_command_table();
	return (true);
}

bool	ft_parse_command(char *buffer, char **env)
{
	if (!env || !buffer)
		return (false);
	printf("parsing\n");
	return (true);
}

int	main(int ac, char **av, char **env)
{
	char	*buffer;

	ft_init_environement();
	while (1)
	{
		buffer = readline(PROMPT);
		if (!buffer || ft_str)// if buffer is empty
			printf("\n");
		else if (ft_strncmp(buffer, "exit", 4) == 0)// exit program
		{
			free (buffer);// free buffer
			exit (0);//	exit program
		}
		else
		{
			ft_parse_command(buffer, env);// parsing the buffer into the command table
			ft_execute_command_table(buffer);// executing the command table
			//ft_free_command_table(buffer);// free the command table
		}
	}
	(void)ac;
	(void)av;
}
