/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:14:03 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:40:28 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On retourne un pointer sur le dernier caractere "nbr" trouvé dans "str"    */
/* On calcul la longueur de "str" on regarde dans une boucle les caractères un*/
/* par un incluant le caractère NULL avec le + 1. Si on trouve une valeur egal*/
/* dans "str" on retourne le pointer + le compteur qui va être egal à la      */
/* position du caractere. Si on trouve rien on retourne NULL.				  */

#include "../includes/libft.h"

char	*ft_strrchr(const char *str, int nbr)
{
	int	len;

	len = ft_strlen(str);
	while (len >= 0)
	{
		if (str[len] == (char)nbr)
			return ((char *)str + len);
		len--;
	}
	return (NULL);
}
