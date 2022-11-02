/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/11/01 22:47:30 by dantremb         ###   ########.fr       */
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
	int		nb_token;
	char	**save;
	int		fd;
}					t_cmd;

typedef struct t_shell
{
	char	**env;
	char	*buffer;
	int		nb_cmd;
	pid_t	*pid;
	t_cmd	*cmd;
	char	expand[2];
	char	heredoc[2];
	int		fd_save[2];
}					t_shell;

int		ft_buffer_integrity(t_shell *shell);
int		ft_parse(t_shell *shell);
char	*ft_exp_heredoc(t_shell *shell, char *heredoc);
void	ft_execute_cmd(t_shell *shell, int nb);
void	ft_find_redirect(t_shell *shell, int nb);
void	ft_clean_token(t_shell *shell, char **token);
char	*ft_get_variable(t_shell *shell, char *buffer, int flag);
void	ft_execve(t_shell *shell, int nb);

void	ft_env(t_shell *shell, int flag);
void	ft_unset(t_shell *shell, char *buffer);
void	ft_export(t_shell *shell, char *arg, int flag);
void	ft_cd(t_shell *shell, char *buffer);
void	ft_echo(char **arg);

void	ft_print_table(t_shell *shell);
void	ft_clear_command(t_shell *shell);
void	ft_exit(t_shell *shell, char *msg, int status);
void	ft_heredoc_signal(int signal);
void	ft_signal(int signal);

#endif
