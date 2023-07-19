/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:23:47 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/19 23:39:23 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_countargsaux(int *i, char *str)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t'
		&& !ft_checkspecial(str + *i))
	{
		if (str[*i] == '\'' || str[*i] == '\"')
			*i += ft_skipquotes(str + *i);
		else
			(*i)++;
	}
}
