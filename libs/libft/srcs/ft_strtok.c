/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:21:26 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/27 18:22:25 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_end_buffer(char *ret, char **save)
{
	*save = NULL;
	if (ft_is_only(ret, ' '))
		return (NULL);
	return (ret);
}

char	*ft_strtok(char *buffer, char sep)
{
	static char	*save;
	char		*ret;

	if (!save)
		save = buffer;
	ret = save;
	while (save && *save == ' ')
		save++;
	while (save && *save != sep)
	{
		if (*save == '\0')
			return (ft_end_buffer(ret, &save));
		else if (*save == '\'' || *save == '\"')
		{
			save = strchr(save + 1, *save);
			if (!save)
				return (ret);
			save++;
		}
		else
			save++;
	}
	if (save)
		*save++ = '\0';
	return (ret);
}
