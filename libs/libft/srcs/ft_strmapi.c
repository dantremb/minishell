/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:57:37 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:40:19 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On recois une chaine de caractère "src" ou l'on doit effectuer la fonction */
/* "f" sur chaque caractère de "src". On regarde si "src" est valide sinon on */
/* retourne NULL. On doit retourner le resultat dans une nouvelle chaine de   */
/* caractère. je crée une copie de "src" avec ft_strup et retourne NULL si    */
/* "temp" égal NULL. On tourne en boucle la fonction à appliquer a chaque     */
/* caractère et on retourne le pointer sur notre nouvelle chaine de caractère */

#include "../includes/libft.h"

char	*ft_strmapi(char const *src, char (*f)(unsigned int, char))
{
	int		i;
	char	*temp;

	if (!src)
		return (NULL);
	temp = ft_strdup((char *)src);
	if (!temp)
		return (NULL);
	i = -1;
	while (temp[++i])
		temp[i] = f(i, temp[i]);
	return (temp);
}
