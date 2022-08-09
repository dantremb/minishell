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
	int		infile;
	bool	if_infile;
	int		outfile;
	char	**options;
	char	*path;
	char	*cmd;
}					t_cmd;

typedef struct		s_data
{
	int		nb_cmd;
	t_cmd	**cmds;
}					t_data;
#endif
