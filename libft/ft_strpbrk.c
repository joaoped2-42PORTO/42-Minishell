/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neddy <neddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:42:43 by neddy             #+#    #+#             */
/*   Updated: 2023/07/11 14:42:49 by neddy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpbrk(const char *str, const char *charset)
{
	const char	*s1;
	const char	*s2;

	s1 = str;
	while (*s1)
	{
		s2 = charset;
		while (*s2)
		{
			if (*s1 == *s2)
				return ((char *)s1);
			s2++;
		}
		s1++;
	}
	return (NULL);
}
