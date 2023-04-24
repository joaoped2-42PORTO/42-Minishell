/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 12:38:03 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/05 16:49:31 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*void	ft_test(unsigned int i, char *str)
	{
		*str += i;
	}


int	main()
{
	char	str[] = "aBcDeF";

	ft_striteri(str, ft_test);
	ft_putendl_fd(str, 1);
}*/
