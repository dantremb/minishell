/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 23:16:36 by root              #+#    #+#             */
/*   Updated: 2022/05/17 23:40:10 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Copier "src" à la fin de "dst". Calculer la longueur de "src et "dst".     */
/* Si "dst" est plus grand que "size" qui est le nombre de caractère à copier */
/* ou que size est plus petit ou egal à 0 on retourne le nombre de caractere  */
/* que l'utilisateur voulais copier + la grandeur de "src" On avance ensuite  */
/* notre compteur "i" jusqu'a la fin de "dst" et on copie de "src" dans "dst" */
/* avec un second compteur pour "dst". On ferme la chaine et on retourne le   */
/* le nombre de caractère total de "dst" après la copie					      */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ii;
	size_t	slen;
	size_t	dlen;

	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	if (dlen > size || size <= 0)
		return (size + slen);
	i = 0;
	ii = 0;
	while (dst[i])
		i++;
	while (i < size - 1 && src[ii])
		dst[i++] = src[ii++];
	dst[i] = '\0';
	return (dlen + slen);
}
