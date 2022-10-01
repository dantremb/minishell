/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/01 01:10:44 by dantremb         ###   ########.fr       */
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

typedef struct		cmd_s
{
	char	*buffer;
	char	**token;
}					cmd_t;

typedef struct		shell_s
{
	char	**env;
	char	*buffer;
	int 	nb_cmd;
	pid_t	pid;
	cmd_t	*cmd;
}					shell_t;

/***get prompt***/
int	ft_getprompt(shell_t *shell);

/***environement***/
shell_t	*ft_init_minishell(int ac, char **av, char **env);

/***exit and free***/
void	ft_exit(shell_t *shell, char *msg, int status, int flag);
void	ft_free(shell_t *shell, int flag);
void	ft_signal(int signal);
#endif
