/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:36:02 by dantremb          #+#    #+#             */
/*   Updated: 2022/04/13 10:29:00 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Recois un nombre, vérifie si le nombre correspond au lettre minuscule de la*/
/* table ASCII. Si oui on soustrait 32 à ce nombre et le retourne.			  */

int	ft_toupper(int nbr)
{
	if (nbr >= 'a' && nbr <= 'z')
		nbr -= 32;
	return (nbr);
}
