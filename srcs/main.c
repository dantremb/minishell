/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:49:16 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/26 23:13:31 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	main(int ac, char **argv, char **env)
{
	t_data data;
	
	ft_init_minishell(&data, env, ac, argv);
	data.buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
	while (data.buffer != NULL)
	{
		if (ft_is_only(data.buffer, ' '))
			ft_free(&data, 1);
		else
		{
			add_history(data.buffer);
			ft_free(&data, 1);
		}
		data.buffer = readline("\033[1;33mMini\033[1;31mshell > \033[0;0m");
	}
}

/***environement***/

void	ft_init_minishell(t_data *data, char **envp, int ac, char **argv)
{
	(void)ac;
	(void)argv;

	ft_memset(data, 0, sizeof(t_data));
	env = ft_remalloc(envp, ft_array_size(envp));
	if (env == NULL)
		ft_exit(data, "Error: malloc failed", 12, 0);
}

/***exit***/

void	ft_free(t_data *data, int flag)
{
	if (flag == 1)
		free(data->buffer);
	if (flag <= 2)
		ft_free_array(env);
}

void	ft_exit(t_data *data, char *msg, int status, int flag)
{
	ft_putstr_fd(msg, 2);
	ft_free(data, flag);
	exit(status);
}