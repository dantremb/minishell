/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:00:38 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:39:15 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Dans une boucle jusqu'a ce que le prochaine élément de "lst" sois NULL on  */
/* applique la fonction "f" sur le contenu de l'élément courant et attribu la */
/* valeur de la prochain liste à la liste.									  */

#include "../includes/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
