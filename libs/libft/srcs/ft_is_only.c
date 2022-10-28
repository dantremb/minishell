/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_only.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:12:42 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/27 18:23:25 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

bool	ft_is_only(char *buffer, char c)
{
	int	i;

	i = 0;
	if (!buffer)
		return (false);
	while (buffer[i] != '\0')
	{
		if (buffer[i] != c)
			return (false);
		i++;
	}
	return (true);
}
