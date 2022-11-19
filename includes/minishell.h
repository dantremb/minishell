/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/11/18 21:20:33 by dantremb         ###   ########.fr       */
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
int		ft_parse(t_shell *shell);
char	*ft_get_variable(char *buffer, int flag);
void	ft_env(int flag);
void	ft_unset(char *buffer);
void	ft_export(char *arg, int flag);
void	ft_cd(char *buffer);
void	ft_echo(char **arg);

#endif
