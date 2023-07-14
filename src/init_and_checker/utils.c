/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:24:54 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/13 09:11:31 by joaoped2         ###   ########.fr       */
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
