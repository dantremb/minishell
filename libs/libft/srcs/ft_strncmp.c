/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:15:16 by root              #+#    #+#             */
/*   Updated: 2022/05/17 23:40:22 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* On doit comparer "s1" et "s2" juqu'a "n" nombre de caractère. On compare   */
/* chaque caractere jusqua NULL ou "n" puis dès que l'on trouve une case 	  */
/* identique on quitte la boucle pour faire la soustraction des 2 valeurs     */
/* On retourne alors négatif si "s1" est plus petit que "s2" positif si "s1"  */
/* est plus grand que "s2" et si tous les caractères était égal il va alors   */
/* faire la soustraction sur la derniere case pour retourner 0.				  */

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
