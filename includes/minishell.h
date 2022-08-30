/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/30 11:53:04 by dantremb         ###   ########.fr       */
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
	char	*path;			//for execve path
	int		infile;
	int		outfile;
	
}					t_cmd;

typedef struct		s_data
{
	char	*buffer;		//buffer for readline
	char	*prompt;		//prompt message for readline
	int 	cmd_count;		//count of commands
	t_cmd	*cmd;			//array of cmd

}					t_data;

#endif
