/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:20:54 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/07 14:48:56 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

/*int	main()
{
	char	*c = ft_strdup("ola");
	char	*s = ft_strdup("Xau");
	char	*j = ft_strdup("Obrigado por terem vindo");
	t_list *elem;
	elem = ft_lstnew(c);
	elem ->next = ft_lstnew(s);
	elem ->next ->next = ft_lstnew (j);

	elem = ft_lstlast(elem);
	while (elem != NULL)
	{
		ft_putendl_fd(elem -> content, 1);
		elem = elem -> next;
	}
}*/
