/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 22:24:10 by root              #+#    #+#             */
/*   Updated: 2022/05/17 23:38:53 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Même fonctionnalité que malloc mais on utilise la fonction ft_bzero pour   */
/* remplir tous l'espace alloué par des carractères NULL. Si l'allocation     */
/* échoue on retoure un pointeur NULL.										  */

#include "../includes/libft.h"

void	*ft_calloc(size_t nbr, size_t size)

{
	void	*tab;

	tab = malloc(size * nbr);
	if (!tab)
		return (NULL);
	ft_bzero(tab, size * nbr);
	return (tab);
}
