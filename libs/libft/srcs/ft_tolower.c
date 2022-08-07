/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:17:54 by dantremb          #+#    #+#             */
/*   Updated: 2022/04/12 22:59:05 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Recois un nombre, vérifie si le nombre correspond au lettre majuscule de la*/
/* table ASCII. Si oui on additionne 32 à ce nombre et le retourne.			  */

int	ft_tolower(int nbr)
{
	if (nbr >= 'A' && nbr <= 'Z')
		nbr += 32;
	return (nbr);
}
