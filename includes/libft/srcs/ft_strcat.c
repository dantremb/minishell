/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:37:15 by dantremb          #+#    #+#             */
/*   Updated: 2022/04/13 10:29:28 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Place le contenu de "src" a la suite du contenu de "dest" si il y a assez  */
/* de place en memoire. on retourne le pointer de destination				  */

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	ii;

	i = 0;
	while (dest[i] != '\0')
		i++;
	ii = -1;
	while (src[++ii] != '\0')
		dest[i + ii] = src[ii];
	dest[i + ii] = '\0';
	return (dest);
}
