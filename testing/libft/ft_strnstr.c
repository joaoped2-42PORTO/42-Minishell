/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:40:02 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/13 14:56:48 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	size;

	if (*s2 == 0)
		return ((char *) s1);
	size = ft_strlen(s2);
	if (len == 0)
		return (0);
	while (*s1 && size <= len)
	{
		if (*s1 == *s2 && ft_strncmp(s1, s2, size) == 0)
			return ((char *)s1);
		++s1;
		--len;
	}
	return (0);
}

/*int	main()
{
	char	str[] = "Indo eu, indo eu";
	char	str1[] = "indo";

	ft_putendl_fd(ft_strnstr(str, str1, ft_strlen(str)), 1);
}*/
