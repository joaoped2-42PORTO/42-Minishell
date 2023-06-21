/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:38:03 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/02 16:49:31 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*s;
	char		*s1;

	if (!dest && !src)
		return (0);
	i = 0;
	s = (char *)src;
	s1 = dest;
	while (i < n)
	{
		s1[i] = s[i];
		i++;
	}
	return (dest);
}

/*int main()
{
	char	str[] = "Vou ser copiado.";
	char	dest[18];

	ft_putstr_fd(ft_memcpy(dest, str, 18), 1);
	ft_putchar_fd('\n', 1);
}*/
