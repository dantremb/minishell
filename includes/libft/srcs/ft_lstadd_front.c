/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:08:30 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:39:09 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On recois une liste "lst" et on doit ajouter l'élément "new" au début de la*/
/* liste "lst" On regarde si une ou l'autre est égal à NULL sinon on quitte la*/
/* fonction. On assigne le prochain element de "new" qui est le premier de la */
/* liste "lst" actuel. Puis ensuite on que le premier pointeur de la liste est*/
/* maintenant egal a "new" 													  */

#include "../includes/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
