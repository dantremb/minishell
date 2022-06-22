/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:19:53 by dantremb          #+#    #+#             */
/*   Updated: 2022/06/21 00:10:44 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_put_char(char src, int *p)
{
	write(1, &src, 1);
	*p += 1;
}

void	ft_put_str(const char *str, int *p)
{
	if (!str)
		ft_put_str("(null)", p);
	else
		while (*str)
			ft_put_char(*str++, p);
}

void	ft_put_ptr(unsigned long ptr, int *p)
{
	ft_put_str("0x", p);
	ft_put_hex(ptr, 16, HEXL, p);
}

void	ft_put_hex(unsigned long nbr, unsigned int base, char *hex, int *p)
{
	if (nbr >= base)
	{
		ft_put_hex(nbr / base, base, hex, p);
		ft_put_hex(nbr % base, base, hex, p);
	}
	else
		ft_put_char(hex[nbr % base], p);
}

void	ft_put_nbr(int nbr, int *p)
{
	if (nbr == -2147483648)
		ft_put_str("-2147483648", p);
	else if (nbr < 0)
	{
		ft_put_char('-', p);
		ft_put_hex(-nbr, 10, DEC, p);
	}
	else
		ft_put_hex(nbr, 10, DEC, p);
}
