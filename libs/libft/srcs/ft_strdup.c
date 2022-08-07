/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:13:15 by root              #+#    #+#             */
/*   Updated: 2022/05/17 23:40:03 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Faire une copie de "src" dans une nouvelle chaine de caractère et retourner*/
/* un pointer vers celle-ci. On calcul la longueur de "src", on alloue la     */
/* memoire du nombre de caractere + 1 pour le NULL. On retourne NULL si		  */
/* l'allocation de memoire n'a pas fonctionner. On peut copier par la suite   */
/* "src" dans "tmp", fermer la chaine puis on retourne le pointer sur "tmp" */

#include "../includes/libft.h"

char	*ft_strdup(const char *src)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (tmp == NULL)
		return (0);
	ft_strlcpy(tmp, src, sizeof(char) * (ft_strlen(src) + 1));
	*(tmp + ft_strlen(src)) = '\0';
	return (tmp);
}
