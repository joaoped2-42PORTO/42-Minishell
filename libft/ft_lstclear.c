/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:49:52 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/13 14:57:25 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*start;

	if (lst == NULL || del == NULL)
		return ;
	start = *lst;
	while (start)
	{
		tmp = start -> next;
		(del)(start -> content);
		free(start);
		start = tmp;
	}
	*lst = NULL;
}

/*void del(void * content)
{
		free(content);
}

int	main()
{
	char	*c = ft_strdup("ola");
	char	*s = ft_strdup("Xau");
	char	*j = ft_strdup("Obrigado por terem vindo");
	t_list *elem;

	elem = ft_lstnew(c);
	elem ->next = ft_lstnew(s);
	elem ->next ->next = ft_lstnew (j);

    ft_lstclear(&elem ->next, &del);
	while (elem != NULL)
    {
    	ft_putendl_fd(elem -> content, 1);
    	elem = elem -> next;
    }
}*/
