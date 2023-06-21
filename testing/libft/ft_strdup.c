/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:03:22 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/02 19:07:27 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dest;
	size_t	i;

	i = ft_strlen(str) + 1;
	dest = malloc(i * sizeof(char));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, str, i);
	return (dest);
}

/*int	main()
{
	char	str[] = "Vou ser duplicado e nem te apercebes!";
	char	str1[] = "Ve o valgrind!";
	char	str2[] = "Ou o pyhtontutor!";

	ft_putendl_fd(ft_strdup(str), 1);
	ft_putendl_fd(ft_strdup(str1), 1);
	ft_putendl_fd(ft_strdup(str2), 1);
}*/
