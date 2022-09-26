/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:58:01 by dantremb          #+#    #+#             */
/*   Updated: 2022/09/25 21:12:12 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_remalloc(char **tab, int size)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_calloc(sizeof(char *) , size);
	if (!tmp)
		return (NULL);
	while (tab[++i])
		tmp[i] = ft_strdup(tab[i]);
	ft_free_array(tab);
	return (tmp);
}
