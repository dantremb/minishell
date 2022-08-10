/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/09 16:47:02 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char **environ;

void	ft_exit_program(t_data *data, char *str)
{
	ft_putstr_fd(str, 2);
	ft_free_array(environ);
	if (data->cmds)
		free (data->cmds);
	exit(0);
}

void	ft_init_environement(t_data *data)
{
	printf("%s\n", "Init environment");
	data->nb_cmd = 0;
	data->cmds = NULL;
}

void	ft_print_command_table(void)
{
	printf("here my command table\n");
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

void	ft_execute_command_table(t_data *data)
{
	if (data->nb_cmd == 0)
	{
		printf("Nothing to execute\n");
	}
	else
	{
		printf("execute the table with = ");
		ft_print_command_table();
	}
}

void	ft_parse_command(t_data *data, int count)
{
	if (count == 0)
	{
		printf("Nothing to parse\n");
	}
	else
	{
		printf("parsing\n");
		data->nb_cmd = count;
		data->cmds = malloc(sizeof(char *) * (count + 1));
		if (data->cmds == NULL)
			ft_exit_program(data, "malloc error");
	}
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

int	main(void)
{
	char	*buffer;
	t_data data;
	
	ft_init_environement(&data);
	while (1)
	{
		buffer = readline(PROMPT);
		if (ft_is_only_space(buffer))// if buffer is empty
			continue ;
		else if (ft_strncmp(buffer, "env", 3) == 0)
		{
			while (*environ)
			{
				printf("%s\n", *environ);
				environ++;
			}
		}
		else if (ft_strncmp(buffer, "exit ", 4) == 0)// exit program
		{
			free (buffer);// free buffer
			exit (0);//	exit program
		}
		else
		{
			ft_parse_command(&data, ft_number_of_command(buffer));// parsing the buffer into the command table
			ft_execute_command_table(&data);// executing the command table
			//ft_free_command_table(buffer);// free the command table
		}
	}
}
