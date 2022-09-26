/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/26 00:14:39 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
t_data data;

int	main(int ac, char **argv, char **env)
{
	ft_init_environement(env, ac, argv);
	signal(SIGINT, ft_signal);
	data.buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
	while (data.buffer != NULL)
	{
		if (ft_is_only(data.buffer, ' '))
			free (data.buffer);
		else
		{
			add_history(data.buffer);
			if (ft_parse_cmd())
				ft_execute_cmd(0);
			else
				free(data.buffer);
		}
		ft_update_error();
		data.buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
	}
}

void	ft_update_error()
{
	char	*tmp;
	char 	*error;
	
	error = ft_itoa(data.err);
	tmp = ft_strjoin("?=", error, 0);
	ft_export(tmp, 0);
	free(tmp);
	free(error);
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
		dprintf(2, "------------ TOKEN -----------------\n");
		ft_color(6);
		dprintf(2, "cmd %d = \t", i);
		while (data.cmd[i].token[j])
		{
			ft_color(3);
			dprintf(2, "[\033[1;34m%s\033[1;33m]", data.cmd[i].token[j]);
			j++;
		}
		dprintf(2, "\n");
		i++;
	}
		dprintf(2, "------------------------------------\n");
	ft_color(8);
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
	int	i;

	if (s <= 0)
		ft_putstr_fd(str, 2);
	if (s <= 1)
		free(data.buffer);
	if (s <= 2)
		ft_free_array(data.env);
	if (s <= 3)
	{
		i = -1;
		while (++i < data.cmd_count)
			free(data.cmd[i].token);
	}
	exit(0);
}