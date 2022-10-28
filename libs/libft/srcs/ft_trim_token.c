/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 23:00:44 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/27 18:23:15 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_trim_token(char *token, char sep)
{
	int		i;

	if (!token)
		return (token);
	i = ft_strlen(token) - 1;
	while (token[i] == sep)
	{
		token[i] = '\0';
		i--;
	}
	while (*token == sep)
		token++;
	return (token);
}
