/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:58:01 by dantremb          #+#    #+#             */
/*   Updated: 2022/10/27 18:21:48 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

char	**ft_remalloc(char **old, int size, int f)
{
	char	**new;
	int		i;

	if (old == NULL)
		return (NULL);
	new = ft_calloc(sizeof(char *), (ft_array_size(old) + size));
	if (!new)
		return (NULL);
	i = -1;
	while (old[++i])
		new[i] = ft_strdup(old[i]);
	if (f == 1)
		ft_free_array(old);
	return (new);
}
