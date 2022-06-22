/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/06/21 23:00:03 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char *command)
{
	ft_printf("%s\n", command);
}

int	main(int ac, char **av, char **env)
{
	char	*buffer;
	int		run;
	int		i;
	char	*command;
	char	sep[2] = {34, 0};

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
			command = ft_substr(buffer, 5, ft_strlen(buffer) - 5);
			command = ft_strtrim(command, sep);
			ft_echo(command);
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
