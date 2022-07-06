/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:14:44 by dantremb          #+#    #+#             */
/*   Updated: 2022/06/30 14:39:24 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_split_size(char *src, char sep)
{
	int		words;
	int		i;

	i = 0;
	words = 0;
	while (src[i])
	{
		while (src[i] == sep)
			i++;
		if (src[i] != sep && src[i])
			words++;
		while (src[i] != sep && src[i])
			i++;
	}
	return (words);
}
