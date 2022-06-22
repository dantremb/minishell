/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:57:32 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:40:04 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On recois une chaine de caractère "src" ou l'on doit effectuer la fonction */
/* "f" sur chaque caractère de "src". On regarde si "src" est valide sinon on */
/* retourne NULL. On tourne en boucle la fonction à appliquer en specifiant   */
/* l'addresse de chaque caractere dans la fonction pour aller modifier la case*/
/* memoire et le premier argument de la fonction demain etait le compteur	  */

#include "../includes/libft.h"

void	ft_striteri(char *src, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (!src)
		return ;
	i = -1;
	while (++i < ft_strlen(src))
		f(i, &src[i]);
}
