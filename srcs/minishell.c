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

int	ft_print_variable(char *command)
{
	int	i;
	(void)command;
	
	i = 0;
	while (command[i])
	{
		ft_putchar(command[i++]);
		if (command[i] == ')')
			break ;
	}
	return(i + 2);
}

void	ft_echo(char *command)
{
	int	i;
	int	jump;
	char set[2];

	set[0] = '"';
	set[1] = '\0';
	i = -1;
	command = ft_strtrim(command, set);
	while (command[++i])
	{
		jump = 0;
		if (command[i] != '$')
			ft_putchar(command[i]);
		else
		{
			jump = ft_print_variable(command + 2);
			i += jump;
		}
	}
	ft_putchar('\n');
}

int	main(int ac, char **av, char **env)
{
	char	*buffer;
	int		run;
	int		i;

	i = 0;
	run = 0;
	while (run != 1)
	{
		buffer = readline("\033[0;32mWHAT THE SHELL !?$>\033[0;37m");
		if (ft_strncmp(buffer, "env", 3) == 0)
		{
			while (env[++i])
				ft_printf("%s\n", env[i]);
		}
		else if (ft_strncmp(buffer, "echo", 4) == 0)
		{
			ft_echo(buffer + 5);
		}
		else if (ft_strncmp(buffer, "exit", 4) == 0)
		{
			exit (0);
		}
		else
			ft_printf("\033[0;31mWhat the Shell you Doing?\n\033[0;37m");
	}
	(void) ac;
	(void) av;
}
