/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/18 22:39:17 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libs/libft/includes/libft.h"

typedef struct		s_cmd
{
	char	*buffer;		//indivividual buffer
	char	**token;		//tokenized buffer
	int		fd_in;			//for open input file
	int		fd_out;			//for open output file
		
}					t_cmd;

typedef struct		s_data
{
	char	**env;			//copy of env
	char	*buffer;		//buffer for readline
	char	*prompt;		//prompt message for readline
	int 	cmd_count;		//count of commands
	char	expand[2];		//flag for expansion
	char	heredoc[2];		//flag for heredoc
	t_cmd	*cmd;			//array of cmd
}					t_data;

#endif

void	ft_cd(char *buffer);
void	ft_export(char *arg);
void	ft_unset(char *buffer);
void	ft_env(int flag);
void	ft_echo(char **arg);
void	ft_free_table(void);
void	ft_exit(char *str, int s);
void	ft_print_table(void);
char	*ft_get_variable(char *buffer);
char	*ft_get_prompt(void);
void 	ft_parse_cmd(void);

