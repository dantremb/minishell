/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:57:26 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:39:46 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* On recois un integer à imprimer sur un FileDescriptor recu dans la fonction*/
/* Si le chiffre est le maximum négatif du integer on dois l'imprimer car on  */
/* ne peut pas le rendre positif sans alterer la valeur a cause du manque de  */
/* memoire pour faire le calcul. Sinon on place le signe négatif en premier et*/
/* envoi le nombre positif à la fonction en récursion donc les étapes analysés*/
/* en premier seront imprimé en dernier. J'envoi le nombre plus petit d'une   */
/* dizaine pour imprimer le reste ensuite donc quand le nombre sera plus petit*/
/* que 10 la recursion arrete et imprime les caractères en quittant chaque    */
/* fonction appelé*/

#include "../includes/libft.h"

void	ft_putnbr_fd(int nbr, int fd)
{
	if (nbr != -2147483648)
	{
		if (nbr < 0)
		{
			ft_putchar_fd('-', fd);
			ft_putnbr_fd(-nbr, fd);
		}
		else
		{
			if (nbr > 9)
				ft_putnbr_fd(nbr / 10, fd);
			ft_putchar_fd('0' + nbr % 10, fd);
		}
	}
	else
		ft_putstr_fd("-2147483648", fd);
}
