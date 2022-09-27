/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/26 22:56:11 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/includes/libft.h"

char	**env;

typedef struct		s_cmd
{
	char	*buffer;
	char	**token;
}					t_cmd;

typedef struct		s_data
{
	char	*buffer;
	int 	nb_cmd;
	t_cmd	*cmd;
}					t_data;

/***environement***/
void	ft_init_minishell(t_data *data, char **envp, int ac, char **argv);

/***exit and free***/
void	ft_exit(t_data *data, char *msg, int status, int flag);
void	ft_free(t_data *data, int flag);

#endif
