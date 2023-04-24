/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 22:50:22 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/05 12:44:03 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char			*sub;
	size_t			i;
	unsigned int	st;

	i = 0;
	st = start;
	sub = malloc(sizeof(char) * len + 1);
	if (!sub || !str)
		return (NULL);
	while (start < ft_strlen(str) && i < len)
	{
		sub[i] = str[st];
		i++;
		st++;
	}
	sub[i] = '\0';
	return (sub);
}

/*int	main()
{
	char	str[] = "Mais um pouco e era Sub-Zero!";

	ft_putendl_fd(ft_substr(str, 20, 30), 1);
}*/
