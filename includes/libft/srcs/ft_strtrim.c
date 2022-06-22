/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:57:39 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:40:31 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On doit retirer les caractères contenu dans "set" au début et à la fin de  */
/* "src" si les caractères de "str" ne correspond plus à ceux de "sep" on     */
/* arrête de trimmé. On commence par regarder si "src" et "set" sont valide   */
/* sinon on retourne NULL. On commence a regarder si "src" est égal à un des  */
/* caractère dans "set". Tant que la condition est valide on avance notre     */
/* pointer de "src". On place dans "end" la longueur de "src" et commence à   */
/* vérifié à partir de la fin si les caractères de "set" se retrouve dans à la*/
/* fin sinon on soustrait 1 de "len". Au final on retourne un nouveau pointeur*/
/* sur une chaine sans les caractères de "set" donc j'utilise ft_substr en lui*/
/* envoyant la "src", 0 comme début car le pointeur à été avancé puis "end +1"*/
/* comme longueur qui correspond au dernier caractère valide + 1 pour NULL.	  */

#include "../includes/libft.h"

char	*ft_strtrim(char const *src, char const *set)
{
	int	end;

	if (!src || !set)
		return (NULL);
	while (*src && ft_strchr(set, *src))
		src++;
	end = ft_strlen(src);
	while (end && ft_strchr(set, src[end]))
		end--;
	return (ft_substr(src, 0, end + 1));
}
