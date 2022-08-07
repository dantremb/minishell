/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:11:10 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:39:29 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Regarde chaque octet des 2 zones de mémoire pointé par "s1" et "s2" puis   */
/* retourne la soustraction de la valeur en caractère des 2 zones mémoire dès */
/* que les 2 zones ne sont pas identique.									  */
/* retour positif si "s1" plus grand que "s2 "					 		      */
/* retour négatif si "s1" plus petit que "s2 "							  	  */
/* retour 0 si "s1" est égal à "s2 "									 	  */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len)
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	return (0);
}
