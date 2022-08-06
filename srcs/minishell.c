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

int	ft_parse_command(char *buffer, char **env)
{
	if (!buffer && !env)
	{
		printf("parsing\n");
		return (0);
	}
	return (1);
}

void	ft_print_command_table(void)
{
	printf("here my table\n");
}

int	main(int ac, char **av, char **env)
{
	char	*buffer;
	(void)ac;
	(void)av;

	error = 0;
	while (1)
	{
		buffer = readline(PROMPT);
		if (ft_parse_command(buffer, env))//Parsing the buffer into the command table
			ft_print_command_table();//Executing the command table
		else if (ft_strncmp(buffer, "exit", 4) == 0)//leave program
			exit (0);
		free(buffer);
	}
}
