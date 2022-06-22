/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:00:13 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:39:22 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Créez une nouvelle variable de type t_list. On alloue la memoire de la     */
/* grandeur d'une t_list. Le contenu de temp est égal à "content". le prochain*/
/* element est NULL. On retourne "temp" 									  */

#include "../includes/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*temp;

	temp = malloc(sizeof(t_list));
	if (!temp)
		return (NULL);
	temp->content = content;
	temp->next = NULL;
	return (temp);
}
