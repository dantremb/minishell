/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:35:05 by root              #+#    #+#             */
/*   Updated: 2022/05/17 23:40:13 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On copie "src" dans "dest" mais seulement un nombre "size" de caractère.   */
/* On calcule la grandeur de "src". Si "size" égal 0 on retourne la grandeur  */
/* de "src" sinon on copie "src" dans "dst" jusqu'a ce qu'on arrive à "size"-1*/
/* pour fermer la chaine par la suite. On retourne la grandeur de "src"		  */

#include "../includes/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(src);
	if (size == 0)
		return (len);
	while (src[i] != '\0' && i < (size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}
