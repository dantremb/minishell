/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:59:17 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:39:13 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Si la liste "lst" et la fonction "del" sont valide on execute la fonction  */
/* sur le contenue de la liste "lst" puis on free(lst)						  */

#include "../includes/libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}
