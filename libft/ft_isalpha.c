/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:36:13 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/02 18:37:43 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

/*int	main()
{
	ft_putnbr_fd(ft_isalpha('a'), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_isalpha('U'), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_isalpha('5'), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_isalpha('\t'), 1);
	ft_putchar_fd('\n', 1);
}*/
