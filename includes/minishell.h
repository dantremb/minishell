/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/11/18 16:07:45 by root             ###   ########.fr       */
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

typedef struct t_cmd
{
	char	*buffer;
	char	**token;
	char	**save;
	int		nb_token;
	int		fd_in;
	int		fd_out;
}					t_cmd;

typedef struct t_shell
{
	char	*buffer;
	int		nb_cmd;
	pid_t	*pid;
	t_cmd	*cmd;
	char	expand[2];
	char	heredoc[2];
	int		error;

}					t_shell;

void	ft_exit(t_shell *shell, char *msg);
int		ft_buffer_integrity(t_shell *shell);

#endif
