/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neddy <neddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:37:57 by neddy             #+#    #+#             */
/*   Updated: 2023/07/11 14:41:30 by neddy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *tofind)
{
	size_t		tofind_len;
	const char	*p1;
	const char	*p2;
	const char	*h;
	const char	*n;

	tofind_len = 0;
	p1 = str;
	p2 = tofind;
	while (*p2++)
		tofind_len++;
	while (*p1)
	{
		h = p1;
		n = tofind;
		while (*h && *n && *h == *n)
		{
			h++;
			n++;
		}
		if (*n == '\0')
			return ((char *)p1);
		p1++;
	}
	return (NULL);
}
