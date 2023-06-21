/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 22:41:48 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/03 22:41:48 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	i1;
	char	*str;

	str = 0;
	if (s1 != 0 && set != 0)
	{
		i = 0;
		i1 = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[i1 - 1] && ft_strchr(set, s1[i1 - 1]) && i1 > i)
			i1--;
		str = malloc(sizeof(char) * (i1 - i + 1));
		if (str)
			ft_strlcpy(str, &s1[i], i1 - i + 1);
	}
	return (str);
}

/*int	main()
{
	char	str[] = "Where's Wally?";
	char	str1[] = "Wally";

	ft_putendl_fd(ft_strtrim(str, str1), 1);
}*/
