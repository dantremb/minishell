/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:00:01 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:39:11 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On doit lancer la fonction "del" sur l'élément de la liste "lst" et tous   */
/* les suivants. Si "lst" est vide on quit la fonction. On va avancer dans les*/
/* éléments avec notre element "temp" qui sera égal au prochain élément. On   */
/* execute la fonction sur le premier élément. "lst" est mainetant égal à temp*/
/* qui était égal au suivant. On continue dans la boucle jusqu'a ce que le    */
/* prochain sois null et lst sera égal à NULL à la fin						  */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, *del);
		(*lst) = temp;
	}
	*lst = NULL;
}
