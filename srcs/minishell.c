/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 00:04:50 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/22 00:50:22 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
t_data data;

char	*ft_get_prompt(void);

int	main(int ac, char **argv, char **env)
{
	char	*prompt;
	
	ft_init_environement(env, ac, argv);
	while (1)
	{
		prompt = ft_get_prompt();
		data.buffer = readline(prompt);
		free(prompt);
		if (ft_is_only(data.buffer, ' '))
			continue;
		else
		{
			add_history(data.buffer);
			ft_parse_cmd();
			ft_execute_cmd(0);
			ft_free_table();
		}
	}
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
		printf("------------ TOKEN -----------------\n");
		ft_color(6);
		printf("cmd %d = \t", i);
		while (data.cmd[i].token[j])
		{
			ft_color(3);
			printf("[\033[1;34m%s\033[1;33m]", data.cmd[i].token[j]);
			j++;
		}
		printf("\n");
		i++;
	}
		printf("------------------------------------\n");
	ft_color(0);
}

char	*ft_get_prompt(void)
{
	char	*prompt;

	prompt = ft_strjoin("\033[0;32m", ft_get_variable("USER"), 0);
	prompt = ft_strjoin(prompt, "@", 1);
	prompt = ft_strjoin(prompt, "minishell", 1);
	prompt = ft_strjoin(prompt, ": ", 1);
	prompt = ft_strjoin(prompt, "\033[0;33m", 1);
	prompt = ft_strjoin(prompt, ft_get_variable("PWD"), 1);
	prompt = ft_strjoin(prompt, "> ", 1);
	prompt = ft_strjoin(prompt, "\033[0m", 1);
	return (prompt);
}
