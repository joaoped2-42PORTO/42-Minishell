/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 01:15:40 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/19 01:15:41 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *str, int c)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != (char)c)
		i++;
	if ((char)c == str[i])
		return ((char *)str + i);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
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
	total = malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
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

char	*ft_strdup(char *str)
{
	char	*dest;
	size_t	i;
	size_t	i1;

	i = ft_strlen(str) + 1;
	i1 = 0;
	dest = malloc(i * sizeof(char));
	if (!dest)
		return (NULL);
	while (i1 < i)
	{
		dest[i1] = str[i1];
		i1++;
	}
	return (dest);
}

void	*ft_calloc(size_t n, size_t daty)
{
	char	*total;
	size_t	i;

	total = malloc(n * daty);
	i = 0;
	if (!total)
		return (NULL);
	while (i < (n * daty))
	{
		total[i] = '\0';
		i++;
	}
	return (total);
}
