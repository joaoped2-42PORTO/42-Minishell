/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:39:05 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/02 18:43:14 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	i1;
	char	*ptr_src;

	i = 0;
	i1 = 0;
	ptr_src = (char *)src;
	while (i < n && *dest)
	{
		dest++;
		i++;
	}
	if (i == n)
		return (ft_strlen(src) + i);
	while (ptr_src[i1])
	{
		if (i1 < (n - i - 1))
			*dest++ = ptr_src[i1];
		i1++;
	}
	*dest = 0;
	return (i + i1);
}

/*int	main()
{
	char	dest[] = "nem me vais ver!";
	char	src[] = "nem a mim, mas vais saber o nosso tamanho!";

	ft_putnbr_fd(ft_strlcat(dest, src, 5), 1);
	ft_putchar_fd('\n', 1);
}*/
