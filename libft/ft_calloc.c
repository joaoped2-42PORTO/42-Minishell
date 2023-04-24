/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:27:34 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/02 18:45:43 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t daty)
{
	char	*total;

	total = malloc(n * daty);
	if (!total)
		return (NULL);
	ft_bzero(total, n * daty);
	return (total);
}

/*int main()
{
	ft_calloc(20, sizeof(char));
}*/
