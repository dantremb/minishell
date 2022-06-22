/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:30:15 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:40:01 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On retourne un pointer sur le premier caractere "nbr" trouvé dans "str"    */
/* On calcul la longueur de "str" on regarde dans une boucle les caractères un*/
/* par un incluant le caractère NULL avec le + 1. Si on trouve une valeur egal*/
/* dans "str" on retourne le pointer + le compteur qui va être egal à la      */
/* position du caractere. Si on trouve rien on retourne NULL.				  */

#include "../includes/libft.h"

char	*ft_strchr(const char *str, int nbr)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(str);
	while (++i < len + 1)
		if (str[i] == (char)nbr)
			return ((char *)str + i);
	return (NULL);
}
