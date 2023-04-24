/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:43:41 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/05 14:43:43 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

/*int main()
{
	int	i = 125;
	int	j = -814;
	int	min = -2147483648;
	int	max = 2147483647;

	ft_putstr_fd(ft_itoa(i), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(ft_itoa(j), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(ft_itoa(min), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(ft_itoa(max), 1);
	ft_putchar_fd('\n', 1);
}*/
