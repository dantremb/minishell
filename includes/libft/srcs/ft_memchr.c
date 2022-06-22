/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:54:46 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:39:27 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Regarde une zone mémoire pointé par "src" et défini en taille par "len" à  */
/* la recherche d'un caractère identique à celui recu dans le int "nbr" qui   */
/* sera donc converti en caractère. On retourne un pointer vers la premiere   */
/* zone mémoire ou on retrouve le caractère sinon on retourne NULL.			  */

#include "../includes/libft.h"

void	*ft_memchr(const void *src, int nbr, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
		if (((unsigned char *)src)[i] == (unsigned char)nbr)
			return (&((int *) src)[i]);
	return (NULL);
}
