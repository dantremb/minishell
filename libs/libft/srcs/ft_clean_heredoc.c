/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:49:12 by dantremb          #+#    #+#             */
/*   Updated: 2022/12/09 10:52:18 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_buildin_exit(void)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * 3);
	cmd[0] = ft_strdup("make");
	cmd[1] = ft_strdup("cleandoc");
	cmd[3] = NULL;
	execve("", cmd, NULL);
	exit(0);
}
