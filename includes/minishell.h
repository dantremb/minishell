/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:54:05 by dantremb          #+#    #+#             */
/*   Updated: 2022/08/29 12:34:44 by dantremb         ###   ########.fr       */
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

typedef struct		s_token
{
	char	*token;			//indivividual token
	char	*path;			//for execve path
	int		infile = -1;
	int		outfile;
	
}					t_token;

typedef struct		s_data
{
	int		nb_cmd;			//number of commands
	char	*buffer;		//buffer for readline
	char	*prompt;		//prompt message for readline
	t_token	*token;			//array of token

}					t_data;

#endif
