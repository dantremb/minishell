/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/21 22:28:42 by dantremb         ###   ########.fr       */
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
	char	**save;
}					cmd_t;

typedef struct		shell_s
{
	char	**env;
	char	*buffer;
	int 	nb_cmd;
	pid_t	*pid;
	cmd_t	*cmd;
	char	expand[2];
	char	heredoc[2];
}					shell_t;

#endif
