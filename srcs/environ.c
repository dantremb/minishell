/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 00:46:12 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/22 00:50:35 by dantremb         ###   ########.fr       */
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

void	ft_free_table(void)
{
	int	i;

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
