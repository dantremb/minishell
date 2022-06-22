/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:01:03 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:39:20 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On doit retourner une nouvelle liste qui est le resultat de la fonction "f"*/
/* effectuer sur chaque element de "lst". On recois aussi la fonction "del" si*/
/* on dois supprimé un element. Si "lst" est vide on retourne NULL. On donne  */
/* la valeur du premier element avec ft_lstnew. On avance au prochaine element*/
/* en disant que "lst" est egal au prochain element. On ajoute dans une boucle*/
/* chaque element suivant en utilisant ft_lstadd_back avec notre list comme   */
/* premier argument et un nouvel élément créé a partir de "lst" avec lst_new  */
/* Si un erreur survient on utilise ft_lstclear pour supprimer et libérer la  */
/* liste et retourner NULL ensuite. Quand "lst" n'est plus valide on quitte la*/
/* boucle et retourne la nouvelle liste.									  */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;

	if (!lst)
		return (NULL);
	newlist = ft_lstnew(f(lst->content));
	lst = lst->next;
	while (lst)
	{
		ft_lstadd_back(&newlist, ft_lstnew(f(lst->content)));
		if (ft_lstlast(newlist) == NULL)
		{
			ft_lstclear(&newlist, *del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (newlist);
}
