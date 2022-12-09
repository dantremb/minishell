/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/12/09 13:07:22 by dantremb         ###   ########.fr       */
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
	int		fd;
	int		open_error;
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

int		ft_parse(t_shell *shell);
int		ft_buffer_integrity(t_shell *shell);
char	*ft_get_variable(char *buffer, int flag);
int		ft_find_redirect(t_shell *shell, int nb);
void	ft_clean_token(t_shell *shell, char **token);
void	ft_execute_cmd(t_shell *shell, int nb);
void	ft_parse_export(t_shell *shell, int nb);
void	ft_parse_unset(t_shell *shell, int nb);
void	ft_execve(t_shell *shell, int nb);
int		ft_open(t_cmd *cmd, char *str, int i);
void	ft_clear_command(t_shell *shell);

void	ft_env(int flag);
void	ft_unset(char *buffer);
void	ft_export(t_shell *shell, char *arg, int flag);
void	ft_cd(t_shell *shell, char *buffer);
void	ft_echo(char **arg);

void	ft_signal_off(void);
void	ft_signal_on(void);

void	ft_exit(t_shell *shell, char *msg, int errno);
void	ft_unlink_heredoc(t_shell *shell);
void	ft_export_error(t_shell *shell);

#endif