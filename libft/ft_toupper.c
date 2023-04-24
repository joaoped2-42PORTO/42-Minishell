/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:40:39 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/02 18:39:10 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

/*int	main()
{
	ft_putchar_fd(ft_toupper('a'), 1);
	ft_putchar_fd('\n', 1);
	ft_putchar_fd(ft_toupper('u'), 1);
	ft_putchar_fd('\n', 1);
	ft_putchar_fd(ft_toupper('A'), 1);
	ft_putchar_fd('\n', 1);
	ft_putchar_fd(ft_toupper('5'), 1);
	ft_putchar_fd('\n', 1);
}*/
