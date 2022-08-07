/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:57:18 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:42:12 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Retourne une chaine de caractère qui corespond à la valeur numérique d'un  */
/* integer recu. on commence par vérifier combien de chiffre le nombre est    */
/* composé en le divisant par 10 jusqu'à ce qu'il sois plus petit que 1 et si */
/* le chiffre est négatif on ajoute 1 par alloué la memoire au caractère '-'  */
/* on peut maintenant allouée notre mémoire pour notre chaine de caractère    */
/* placer le signe négatif au besoin, insérer le max integer négarif si tel   */
/* est le cas car on altère la valeur du int en multipliant par -1. puis on   */
/* insère dans chaque caractère la valeur du reste de la division par 10      */
/* jusqu'a ce que "i" sois égal à 0 donc le dernier caractère sera l'unité.   */
/* on retourne ensuite notre chaine de caractère "temp" 					  */

#include "../includes/libft.h"

static int	ft_intlen(int nbr)
{
	int	i;

	if (nbr == 0)
		return (1);
	i = 0;
	if (nbr < 0)
		i++;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nbr)
{
	char	*temp;
	int		i;
	int		sign;

	i = ft_intlen(nbr);
	temp = ft_calloc(ft_intlen(nbr) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	if (nbr == -2147483648)
		return (ft_memcpy(temp, "-2147483648", 11));
	sign = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		sign = 1;
	}
	while (--i >= 0)
	{
		temp[i] = nbr % 10 + '0';
		nbr /= 10;
		if (i == 0 && sign == 1)
			temp[i] = '-';
	}
	return (temp);
}
