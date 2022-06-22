/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:18:53 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:39:18 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On doit retourner le pointeur du dernier élément d'une liste "lst". Si la  */
/* liste est vide on retourne NULL. Tant que le prochain élément est pas NULL */
/* on dit que "lst" est égal au prochain dans la liste. Quand la boucle est   */
/* terminé on renvoi alors le dernier pointeur de "lst"						  */

#include "../includes/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
