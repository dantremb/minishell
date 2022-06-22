/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:19:04 by root              #+#    #+#             */
/*   Updated: 2022/05/17 23:39:33 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* copie la zone mémoire pointé par "src" et délimité par "len" vers la zone  */
/* pointé par "dst". si les 2 pointer recu pointe vers la meme adresse on     */
/* retourne l'adresse de "dest". si l'addresse de "src" est plus petite que   */
/* celle de "dest" on copie chaque caractère à partir de la fin pour éviter   */
/* de copier ce qui à déja été copier. sinon fait la copie de la meme facon   */
/* que ft_memcpy puis on retourne un pointer sur "dst"						  */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = -1;
	if (dst == src)
		return (dst);
	else if (src < dst)
	{
		while (len > 0)
		{	
			((char *)dst)[len - 1] = ((char *)src)[len - 1];
			len--;
		}
	}
	else
	{
		while (++i < len)
			((char *)dst)[i] = ((char *)src)[i];
	}
	return (dst);
}
