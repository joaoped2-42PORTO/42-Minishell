/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:35:17 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/02 18:23:58 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45)
	{
		sign = -1;
		i++;
	}
	else if (str[i] == 43)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

/*int main()
{
	char str1[] = "15613";
	char str2[] = "-15613";
	char str3[] = "+15asd613";
	char str4[] = "-1561dase3";

	ft_putnbr_fd(ft_atoi(str1), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_atoi(str2), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_atoi(str3), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_atoi(str4), 1);
	ft_putchar_fd('\n', 1);
}*/
