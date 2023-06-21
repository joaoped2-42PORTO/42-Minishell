/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:22:12 by joaoped2          #+#    #+#             */
/*   Updated: 2022/11/07 14:50:10 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		return (0);
	}
	new -> content = content;
	new -> next = NULL;
	return (new);
}

/*int	main()
{
	t_list	*elem;
	elem = ft_lstnew("ola");
	elem ->next = ft_lstnew("Xau");
	elem ->next ->next = ft_lstnew ("Obrigado por terem vindo");
	ft_putendl_fd(elem -> content, 1);
	elem = elem ->next;
	ft_putendl_fd(elem ->content, 1);
	elem = elem ->next;
	ft_putendl_fd(elem ->content, 1);
}*/
