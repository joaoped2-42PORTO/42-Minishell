/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:50:21 by huolivei          #+#    #+#             */
/*   Updated: 2022/12/07 11:47:15 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_format(va_list args, const char str)
{
	int	rst;

	rst = 0;
	if (str == 'c')
		rst += ft_putchar(va_arg(args, int));
	else if (str == 's')
		rst += ft_prtstr(va_arg(args, char *));
	else if (str == 'p')
		rst += ft_putadr(va_arg(args, unsigned long long));
	else if (str == 'd' || str == 'i')
		rst += ft_prtnb(va_arg(args, int));
	else if (str == 'u')
		rst += ft_prtunnb(va_arg(args, unsigned int));
	else if (str == 'x' || str == 'X')
		rst += ft_printhex(va_arg(args, unsigned int), str);
	else if (str == '%')
		rst += ft_putchar('%');
	return (rst);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		rst;
	va_list	args;

	i = 0;
	rst = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			rst += get_format(args, str[i + 1]);
			i++;
		}
		else
			rst += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (rst);
}
