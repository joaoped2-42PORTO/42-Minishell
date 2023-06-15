/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:49:37 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/15 14:42:04 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	see_closed_pipe(char *str, int *i)
{
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

int	see_quote_double_string(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '\"')
		{
			if (!see_dbquote_string(str, i))
				return (0);
		}
		else if (str[*i] == '\'')
		{
			if (!see_quote_string(str, i))
				return (0);
		}
		(*i)++;
	}
	return (1);
}

int	valid_input(t_shell *args)
{
	int	i;

	i = 0;
	while (args->input[i] == ' ')
		i++;
	while (args->input[i])
	{
		while (ft_isalnum(args->input[i]))
			i++;
		while (args->input[i] == ' ')
			i++;
		if (!loop_input(args, &i))
			return (0);
		if (args->input[i] != '\0')
			i++;
	}
	return (1);
}
