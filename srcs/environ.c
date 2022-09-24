/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 00:46:12 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/24 01:29:35 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
extern t_data data;

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

int	ft_status(void)
{
	int	i;

	i = 0;
	while (data.buffer[i] && (data.buffer[i] == ' ' || data.buffer[i] == '\t'))
		i++;
	if (data.buffer[i] == '$' && data.buffer[i + 1] == '?')
	{
		printf("%d\n", data.err);
		data.err = 0;
		return (1);
	}
	return (0);
}

void	ft_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		data.err = 130;
	}
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
	data.err = 0;
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
