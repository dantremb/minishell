/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/01 00:43:57 by dantremb         ###   ########.fr       */
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

typedef struct		s_cmd
{
	char	*buffer;
	char	**token;
}					t_cmd;

typedef struct		s_shell
{
	char	**env;
	char	*buffer;
	int 	nb_cmd;
	t_cmd	*cmd;
}					t_shell;

/***get prompt***/
int	ft_getprompt(t_shell *shell);

/***environement***/
t_shell	*ft_init_minishell(int ac, char **av, char **env);

/***exit and free***/
void	ft_exit(t_shell *shell, char *msg, int status, int flag);
void	ft_free(t_shell *shell, int flag);
void	ft_signal(int signal);
#endif
