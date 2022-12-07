/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_closed_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:12:24 by root              #+#    #+#             */
/*   Updated: 2022/12/07 11:56:23 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_check_closed_quote(char *buf)
{
	char	*tmp;

	tmp = buf;
	while (*tmp)
	{
		if (*tmp == '\'' || *tmp == '\"')
		{
			if (ft_strchr(tmp + 1, *tmp) == NULL)
			{
				ft_putstr("Error Quote not closed\n");
				return (1);
			}
			else
				tmp = ft_strchr(tmp + 1, *tmp);
		}
		tmp++;
	}
	return (0);
}
