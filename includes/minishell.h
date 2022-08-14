/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/14 11:36:56 by dantremb         ###   ########.fr       */
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
	//commmand number
	int		id;
	//for redirections
	int		infile;
	int		outfile;
	//for execve and builtins
	char	*cmd;
	char	**options;
	char	*path;
	//buffer after first split
	char	*cmd_buffer;
}					t_cmd;

typedef struct		s_data
{
	//number of commands
	int		nb_cmd;
	//buffer for readline
	char	*buffer;
	//prompt message for readline
	char	*prompt;
	//array of commands
	t_cmd	*cmds;
}					t_data;

#endif
