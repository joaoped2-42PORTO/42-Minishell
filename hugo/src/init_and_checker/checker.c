/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:49:37 by huolivei          #+#    #+#             */
/*   Updated: 2023/05/24 23:46:07 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	see_closed_pipe(char *str, int *i)
{
	while (str[*i])
	{
		(*i)++;
		if (ft_isalnum(str[*i]))
			return (1);
	}
	return (0);
}

int	see_dbquote_string(char *str, int *i)
{
	while (str[*i])
	{
		(*i)++;
		if (str[*i] == '\"')
			return(1);
	}
	return (0);
}

int	see_quote_string(char *str, int *i)
{
	while (str[*i])
	{
		(*i)++;
		if (str[*i] == '\'')
			return (1);
	}
	return (0);
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
		if (args->input[i] == '\'')
		{
			i++;
			if(!see_quote_string(args->input, &i))
				return (0);
			i++;
		}
		else if (args->input[i] == '\"')
		{
			i++;
			if(!see_dbquote_string(args->input, &i))
				return (0);
			i++;
		}
		else if (args->input[i] == '|')
		{
			i++;
			if(!see_closed_pipe(args->input, &i))
				return (0);
		}
	}
	return (1);
}
