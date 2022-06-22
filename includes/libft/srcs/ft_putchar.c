/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 23:42:20 by root              #+#    #+#             */
/*   Updated: 2022/05/17 23:39:39 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* écrit sur la sortie standard le caractère recu dans "src"				  */

#include "../includes/libft.h"

void	ft_putchar(char src)
{
	write(1, &src, 1);
}
