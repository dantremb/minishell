/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:06:46 by dantremb          #+#    #+#             */
/*   Updated: 2022/05/17 23:39:51 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* on recois une chaine de caractère à imprimer. Si la chaine est vide on quit*/
/* la fonction sinon avec une boucle et compteur on imprime chaque caractere  */
/* jusqu'au caractère NULL avec la fonction ft_putchar						  */

#include "../includes/libft.h"

void	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i] != '\0')
		ft_putchar(str[i]);
}
