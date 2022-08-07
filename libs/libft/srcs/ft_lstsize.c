/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:10:18 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:39:24 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On recois une liste "lst" et on dois retourner le nombre d'élément. si la  */
/* liste est vide on retourne NULL. Tant que lst->next n'est pas égal à NULL  */
/* qui n'est donc pas le dernier on ajoute 1 au compteur "size"				  */

#include "../includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	if (!lst)
		return (0);
	size = 0;
	while (++size && lst->next != NULL)
		lst = lst->next;
	return (size);
}
