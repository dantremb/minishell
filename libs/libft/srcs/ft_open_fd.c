/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 18:35:49 by nadesjar          #+#    #+#             */
/*   Updated: 2022/10/31 23:25:43 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_open_fd(char *str, int i)
{
	static int	fd;

	if (i == 1)
		fd = open(str, O_RDONLY, 0644);
	else if (i == 2)
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 3)
		fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (i == 4)
		fd = open(str, O_RDWR | O_CREAT, 0777);
	else if (i == 5)
		fd = open(str, O_WRONLY | O_CREAT, 0777);
	else if (i == 6)
		fd = open(str, O_RDWR | O_APPEND | O_CREAT, 0777);
	if (!fd)
		{
			ft_putstr_fd("minishell: open() error\n", 2);
			return (-1);
		}
	return (fd);
}
