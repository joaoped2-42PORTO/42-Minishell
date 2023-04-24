/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:34:13 by joaoped2          #+#    #+#             */
/*   Updated: 2022/11/07 17:08:13 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
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
	char	*str = ft_strdup("Ola de novo");
	t_list	*str1 = ft_lstnew(str);
    ft_lstadd_front(&elem, str1);
    while (elem != NULL)
    {
    	ft_putendl_fd(elem -> content, 1);
    	elem = elem -> next;
    }
}*/
