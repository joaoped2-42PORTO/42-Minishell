/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptrunin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:40:49 by huolivei          #+#    #+#             */
/*   Updated: 2022/12/04 15:33:39 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_prtadr(unsigned long long ptr)
{
	if (ptr >= 16)
	{
		ft_prtadr(ptr / 16);
		ft_prtadr(ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_putchar(ptr + '0');
		else
			ft_putchar(ptr - 10 + 'a');
	}
}

int	ft_putadr(unsigned long long ptr)
{
	int	rst;

	rst = 0;
	if (ptr == 0)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	rst += write(1, "0x", 2);
	if (ptr > 0)
	{
		ft_prtadr(ptr);
		rst += ft_nbsup16(ptr);
	}
	return (rst);
}

char	*ft_uitoa(unsigned int n)
{
	char	*str;
	int		i;
	long	nb;

	nb = n;
	i = ft_nbsup10(nb);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (0);
	str[i] = '\0';
	while (nb != 0)
	{
		str[i - 1] = nb % 10 + '0';
		nb /= 10;
		i--;
	}
	return (str);
}

int	ft_prtunnb(unsigned int nb)
{
	int		rst;
	char	*str;

	rst = 0;
	if (nb == 0)
		rst = ft_putchar('0');
	else
	{
		str = ft_uitoa(nb);
		rst = ft_prtstr(str);
		free(str);
	}
	return (rst);
}
