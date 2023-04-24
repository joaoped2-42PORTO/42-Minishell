/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:36:38 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/02 18:28:19 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

/*int main()
{
	ft_putnbr_fd(ft_isdigit('5'), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_isdigit('4'), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_isdigit('a'), 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(ft_isdigit('\t'), 1);
	ft_putchar_fd('\n', 1);

}*/
