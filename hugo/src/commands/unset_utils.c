/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:08:32 by huolivei          #+#    #+#             */
/*   Updated: 2023/05/15 12:08:27 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	variable_size(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
		if (str[i] == '=')
			break ;
	}
	return (i);
}
