/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantremb <dantremb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 07:52:43 by dantremb          #+#    #+#             */
/*   Updated: 2022/06/21 00:10:41 by dantremb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		len;

	va_start(arg, str);
	len = 0;
	while (*str)
	{
		if (*str == '%')
			ft_choose_arg(*(str++ + 1), arg, &len);
		else
			ft_put_char(*str, &len);
		str++;
	}
	va_end(arg);
	return (len);
}

void	ft_choose_arg(char str, va_list arg, int *p)
{
	if (str == 's')
		ft_put_str(va_arg(arg, char *), p);
	else if (str == 'c')
		ft_put_char(va_arg(arg, int), p);
	else if (str == '%')
		ft_put_char(str, p);
	else if (str == 'd' || str == 'i')
		ft_put_nbr(va_arg(arg, int), p);
	else if (str == 'p')
		ft_put_ptr(va_arg(arg, unsigned long ), p);
	else if (str == 'u')
		ft_put_hex(va_arg(arg, unsigned int), 10, DEC, p);
	else if (str == 'x')
		ft_put_hex(va_arg(arg, unsigned int), 16, HEXL, p);
	else if (str == 'X')
		ft_put_hex(va_arg(arg, unsigned int), 16, HEXU, p);
}
