/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/09 14:37:56 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//check if system is linux or mac

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include "../libs/libft/includes/libft.h"
# include <stdbool.h>

#define PROMPT "\033[0;32mMINISHELL->\033[0;37m"

typedef struct		s_cmd
{
	//for redirections
	int		infile;
	int		outfile;
	//for execve
	char	**options;
	char	*path;
	char	*cmd;
	//for builtins
	//0=not use 1=echo 2=cd 3=pwd 4=export 5=unset 6=env
	int		builtin;
	//buffer after split command
	char	*cmd_buffer;
}					t_cmd;

typedef struct		s_data
{
	//nunmber of commands
	int		nb_cmd;
	//buffer for readline
	char	*buffer;
	//array of commands
	t_cmd	**cmds;
}					t_data;
#endif
