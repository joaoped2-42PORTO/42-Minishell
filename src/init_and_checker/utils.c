/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:24:54 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/24 19:49:21 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	checkpipered(t_shell *args, int *i)
{
	char	*str;

	str = "echo";
	if (*i != 0)
		if (str_is_equal(args->split[*i - 1], str))
			return (0);
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
		if (str[*i] == '"')
		{
			(*i)++;
			if (!see_dbquote_string(str, i))
				return (0);
			else
				return (1);
		}
		else if (str[*i] == '\'')
		{
			(*i)++;
			if (!see_quote_string(str, i))
				return (0);
			else
				return (1);
		}
		if (str[*i] != ' ' && str[*i] != '\t')
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
