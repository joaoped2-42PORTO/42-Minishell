/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_formats.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:08:32 by huolivei          #+#    #+#             */
/*   Updated: 2022/12/04 15:34:34 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_prtstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_nbsup16(unsigned long long nb)
{
	int	rst;

	rst = 0;
	while (nb != 0)
	{
		nb /= 16;
		rst++;
	}
	return (rst);
}

int	ft_nbsup10(unsigned int nb)
{
	int	rst;

	rst = 0;
	while (nb != 0)
	{
		nb /= 10;
		rst++;
	}
	return (rst);
}

int	ft_putchar(int c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_prtnb(int nb)
{
	int		rst;
	char	*str;

	str = ft_itoa(nb);
	rst = ft_prtstr(str);
	free(str);
	return (rst);
}
