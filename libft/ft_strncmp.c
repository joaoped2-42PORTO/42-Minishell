/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:39:49 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/02 18:20:08 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && i < (n - 1))
			i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*int	main()
{
	char	str[] = "Sera que sou grande?";
	char	str1[] = "Ou sera que eu ainda sou maior?";

	ft_putnbr_fd(ft_strncmp(str, str1, 5), 1);
	ft_putchar_fd('\n', 1);
}*/
