/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:49:27 by huolivei          #+#    #+#             */
/*   Updated: 2022/11/13 14:56:07 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	(*del)(lst -> content);
	free (lst);
}

/*void del(void *content)
{
	if (content != NULL)
		free(content);
	ft_putendl_fd("Fui liberto", 1);
}

int	main()
{
	char	*c = ft_strdup("ola");
	t_list *elem;
	elem = ft_lstnew(c);
	ft_lstdelone(elem , del);
}*/
