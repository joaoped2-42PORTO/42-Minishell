/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:40:26 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/02 16:41:49 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

/*int	main()
{
	ft_putchar_fd(ft_tolower('C'), 1);
	ft_putchar_fd('\n', 1);
	ft_putchar_fd(ft_tolower('A'), 1);
	ft_putchar_fd('\n', 1);
	ft_putchar_fd(ft_tolower('z'), 1);
	ft_putchar_fd('\n', 1);
	ft_putchar_fd(ft_tolower('4'), 1);
	ft_putchar_fd('\n', 1);
}*/
