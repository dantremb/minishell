/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/17 23:00:39 by dantremb         ###   ########.fr       */
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
	int		id;				//commmand number
	int		infile;			//redirections input
	int		outfile;		//redirections output
	char	*cmd;			//builtin buffer
	char	**options; 		//for execve options
	char	*path;			//for execve path
	char	*cmd_buffer;	//individual command buffer
}					t_cmd;

typedef struct		s_data
{
	int		nb_cmd;			//number of commands
	char	*buffer;		//buffer for readline
	char	*prompt;		//prompt message for readline
	t_cmd	*cmds;			//array of commands

}					t_data;

#endif
