/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:17:49 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/07 17:33:14 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*tmp;

	start = NULL;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst -> content));
		if (!tmp)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		ft_lstadd_back(&start, tmp);
		lst = lst -> next;
	}
	return (start);
}

/*void	*ft_new(void *content)
{
	return("Como novo!");
}

void	ft_del(void *content)
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

	t_list *new = ft_lstmap(elem, ft_new, ft_del);
	while (new != NULL)
    {
    	ft_putendl_fd(elem -> content, 1);
		ft_putendl_fd(new -> content, 1);
		new = new -> next;
    	elem = elem -> next;
    }
}*/
