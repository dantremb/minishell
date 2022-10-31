/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/31 13:36:27 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "readline.h"
# include "history.h"
# include "rlstdc.h"
# include <sys/wait.h>
# include <stdio.h>
# include <signal.h>
# include "../libs/libft/includes/libft.h"

typedef struct	s_cmd
{
	char	*buffer;
	char	**token;
	int		nb_token;
	char	**save;
}	t_cmd;

typedef struct	s_shell
{
	char	**env;
	char	*buffer;
	int 	nb_cmd;
	pid_t	*pid;
	t_cmd	*cmd;
	char	expand[2];
	char	heredoc[2];
	int		save_fd[2];
}	t_shell;

#endif
