/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:24:54 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/08 23:07:45 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	checkpipered(t_shell *args, int *i)
{
	if (args->split[*i][0] == '|')
		return (1);
	return (0);
}

int	see_closed_pipe(char *str, int *i)
{
	if (str[*i] == '|')
		return (0);
	while (str[*i])
	{
		if (ft_isalnum(str[*i]))
			return (1);
		(*i)++;
	}
	return (0);
}

int	see_dbquote_string(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '\"')
			return (1);
		(*i)++;
	}
	return (0);
}

int	see_quote_string(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '\'')
			return (1);
		(*i)++;
	}
	return (0);
}