/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:57:41 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:40:34 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Retourne un pointeur vers une nouvelle chaine de caractère provenant de la */
/* chaine "src" Elle contient les caractères qui débute à "start" jusqu'à une */
/* longueur "len". Si "src" est vide on retourne NULL. On calcul la longueur  */
/* de "src". Si "start" est plus grand que la longueur de "src" on retourne un*/
/* pointer vide. Sinon on alloue la mémoire puis on copie "src" dans "tmp"    */
/* on retourne le pointeur "tmp"											  */

#include "../includes/libft.h"

char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	size_t			i;
	size_t			slen;
	char			*tmp;

	if (!src)
		return (NULL);
	slen = ft_strlen((char *)src);
	if (start > slen)
		return (ft_strdup(""));
	tmp = malloc((len + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	i = -1;
	while (++i < len)
		tmp[i] = src[start + i];
	tmp[i] = '\0';
	return (tmp);
}
