/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:38:42 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/02 18:09:53 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;
	char	*str1;

	i = 0;
	str1 = str;
	while (i < n)
	{
		str1[i] = c;
		i++;
	}
	return ((void *)str1);
}

/*int main()
{
	char	str[] = "Ola bom dia";
	char	c = 'u';

	ft_putstr_fd(ft_memset(str, c, 12), 1);
	ft_putchar_fd('\n', 1);
}*/
