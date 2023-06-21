/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:39:18 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/02 18:33:40 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t len)
{
	size_t	i;

	if (!len)
		return (ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && i < (len - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

/*int	main()
{
	char	dest[] = "nem me vais ver!";
	char	src[] = "nem a mim, mas vais saber o nosso tamanho!";

	ft_putnbr_fd(ft_strlcpy(dest, src, 20), 1);
	ft_putchar_fd('\n', 1);
}*/
