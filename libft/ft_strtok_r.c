/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neddy <neddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:36:30 by neddy             #+#    #+#             */
/*   Updated: 2023/07/11 14:36:53 by neddy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok_r(char *str, const char *delim, char **saveptr)
{
	char	*token;

	if (str != NULL)
		*saveptr = str;
	if (*saveptr == NULL || **saveptr == '\0')
		return (NULL);
	token = *saveptr;
	*saveptr = ft_strpbrk(token, delim);
	if (*saveptr != NULL)
		*(*saveptr)++ = '\0';
	return (token);
}
