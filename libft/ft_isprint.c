/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:36:49 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/02 16:41:13 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/*int	main()
{
	ft_putnbr_fd(ft_isprint(45), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_isprint(19), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_isprint(127), 1);
	ft_putchar_fd('\n', 1);
}*/
