/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/26 23:15:40 by dantremb         ###   ########.fr       */
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
	int		nb_token;
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
	int		save_fd[2];
}					shell_t;

int		ft_buffer_integrity(shell_t *shell);
int 	ft_parse(shell_t *shell);
void	ft_execute_cmd(shell_t *shell, int nb);
void	ft_redirect(cmd_t *cmd, char *meta, int side, int flag);
void	ft_clean_token(shell_t *shell, char **token);
char	*ft_get_variable(shell_t *shell, char *buffer, int flag);
void	ft_execve(shell_t *shell, int nb);

void	ft_env(shell_t *shell, int flag);
void	ft_unset(shell_t *shell, char *buffer);
void	ft_export(shell_t *shell, char *arg, int flag);
void	ft_cd(shell_t *shell, char *buffer);
void	ft_echo(char **arg);

void	ft_print_table(shell_t *shell);
void	ft_clear_command(shell_t *shell);
void	ft_exit(shell_t *shell, char *msg, int status);
void	ft_heredoc_signal(int signal);
void	ft_signal(int signal);

#endif