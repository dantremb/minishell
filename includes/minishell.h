/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/08 15:47:37 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include "../libs/libft/includes/libft.h"
# include <stdbool.h>


typedef struct		s_cmd
{
	char	*buffer;		//indivividual buffer
	char	**token;		//tokenized buffer
	
	char	*infile;		//name of file to open for input
	int		fd_in;			//fd to open the input file
	
	char	*outfile;		//name of file to open for output
	char	*outappend;		//name of file to open for output in append mode
	int		fd_out;			//fd for open output file
	
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
