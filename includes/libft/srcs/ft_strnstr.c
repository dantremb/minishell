/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:43:58 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:40:25 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Chercher "find" dans "str". Si "find" égal NULL on retourne "str" tant que */
/* "str" est valide. Si "str" et "find" sont identique on entre dans 2e boucle*/
/* si "find" est trouvé au complet on retourne notre pointeur "str + compteur"*/
/* si rien n'est trouvé on retourne NULL.									  */

#include "../includes/libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	s;
	size_t	f;

	s = 0;
	if (find[s] == '\0')
		return ((char *)str);
	while (str[s] != '\0' && s < len)
	{
		f = 0;
		while (str[s + f] == find[f] && s + f < len)
		{
			if (find[f + 1] == '\0')
				return ((char *)str + s);
			f++;
		}
		s++;
	}
	return (0);
}
