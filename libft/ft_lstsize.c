/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:46:02 by joaoped2          #+#    #+#             */
/*   Updated: 2022/11/07 12:12:05 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		++i;
	}
	return (i);
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

	ft_putnbr_fd(ft_lstsize(elem), 1);
	ft_putchar_fd('\n', 1);
	while (elem != NULL)
    {
    	ft_putendl_fd(elem -> content, 1);
    	elem = elem -> next;
    }
}*/
