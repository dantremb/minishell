/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/24 01:45:35 by dantremb         ###   ########.fr       */
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
	int		fd_in;
	int		fd_out;
	pid_t	pid;
}					t_cmd;

typedef struct		s_data
{
	char	**env;
	char	*buffer;
	int 	cmd_count;
	char	expand[2];
	char	heredoc[2];
	t_cmd	*cmd;
	int		err;
}					t_data;

void	ft_cd(char *buffer);
void	ft_export(char *arg);
void	ft_unset(char *buffer);
void	ft_env(int flag);
void	ft_echo(char **arg);
void	ft_exit(char *str, int s);
void	ft_free_table(void);
void	ft_print_table(void);
char	*ft_get_variable(char *buffer);
char	*ft_get_path(int nb);
int 	ft_parse_cmd(void);
void	ft_execute_cmd(int nb);
void	ft_clean_token(char **token);
void	ft_init_environement(char **env, int ac, char **argv);
void	ft_signal(int signal);
int		ft_check_closed_quote(char *buf);
int		ft_status(void);
void	ft_update_error();
char	*ft_get_prompt(void);

#endif
	