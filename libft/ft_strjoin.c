/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 23:35:00 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/05 12:43:09 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		i1;
	char	*total;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	total = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1 * sizeof(char));
	if (!total)
		return (NULL);
	i = 0;
	i1 = 0;
	while (s1[i] != '\0')
		total[i1++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		total[i1++] = s2[i++];
	total[i1] = '\0';
	return (total);
}

/*int	main()
{
	char	str[] = "Junta te a mim, ";
	char	str1[] = "nos ja vivemos 100 mil anos!";

	ft_putendl_fd(ft_strjoin(str, str1), 1);
}*/
