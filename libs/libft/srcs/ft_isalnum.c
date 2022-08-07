/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:27:01 by root              #+#    #+#             */
/*   Updated: 2022/04/10 23:00:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Retourne 1 si on trouve un caractère alphabétique ou numérique sinon 0. 	  */

int	ft_isalnum(int nbr)
{
	if ((nbr >= 'a' && nbr <= 'z') || (nbr >= 'A' && nbr <= 'Z')
		|| (nbr >= '0' && nbr <= '9'))
		return (1);
	return (0);
}
