/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:11:18 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/07 17:15:29 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		(*f)(lst -> content);
		lst = lst -> next;
	}
}

/*void ft_iter(void *content)
{
	char	*str = (char *)content;
	int	i = 0;
	while(str[i])
	{
		if(str[i] >= 65 && str[i] <= 90)
		{
			str[i] += 32;
		}
		else if(str[i] >= 97 && str[i] <= 122)
		{
			str[i] -= 32;
		}
		i++;
	}
}

int	main()
{
	char	*c = ft_strdup("OLa");
	t_list *elem;
	elem = ft_lstnew(c);

	ft_lstiter(elem, ft_iter);
	ft_putendl_fd(elem -> content, 1);
}*/
