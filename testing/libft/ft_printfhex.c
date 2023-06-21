/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfhex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 21:15:39 by huolivei          #+#    #+#             */
/*   Updated: 2022/12/04 15:16:29 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex(unsigned int nb, const char str)
{
	if (nb >= 16)
	{
		ft_puthex(nb / 16, str);
		ft_puthex(nb % 16, str);
	}
	else
	{
		if (nb <= 9)
			ft_putchar(nb + '0');
		else
		{
			if (str == 'x')
				ft_putchar(nb - 10 + 'a');
			if (str == 'X')
				ft_putchar(nb - 10 + 'A');
		}
	}
}

int	ft_printhex(unsigned int nb, const char str)
{
	if (nb == 0)
		return (ft_putchar('0'));
	else
		ft_puthex(nb, str);
	return (ft_nbsup16(nb));
}

int	numlen(long n)
{
	int	rst;

	rst = 0;
	if (n <= 0)
	{
		n *= -1;
		rst++;
	}
	while (n > 0)
	{
		n /= 10;
		rst++;
	}
	return (rst);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nb;

	nb = n;
	i = numlen(nb);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	else if (nb == 0)
		str[0] = '0';
	str[i--] = '\0';
	while (nb)
	{
		str[i] = nb % 10 + '0';
		i--;
		nb /= 10;
	}
	return (str);
}
