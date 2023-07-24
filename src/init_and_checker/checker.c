/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:49:37 by huolivei          #+#    #+#             */
/*   Updated: 2023/07/24 19:52:57 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	loop_input_helper(t_shell *args, int *i)
{
	if ((args->input[*i] == '\'' && args->input[*i + 1] == '\'')
		|| (args->input[*i] == '\"' && args->input[*i + 1] == '\"'))
	{
		(*i)++;
		if (!see_quote_double_string(args->input, i))
			return (0);
	}
	return (1);
}

int	loop_input(t_shell *args, int *i)
{
	if (loop_input_helper(args, i) == 0)
		return (0);
	else if (args->input[*i] == '\'')
	{
		(*i)++;
		if (!see_quote_string(args->input, i))
			return (0);
	}
	else if (args->input[*i] == '\"')
	{
		(*i)++;
		if (!see_dbquote_string(args->input, i))
			return (0);
	}
	else if (args->input[*i] == '|')
	{
		(*i)++;
		if (!see_closed_pipe(args->input, i))
			return (0);
	}
	return (1);
}

int	see_red_closed(char *str, int i)
{
	if ((str[i] == '>' && str[i + 1] == '<')
		|| (str[i] == '<' && str[i + 1] == '>' && str[i + 2] == '>')
		|| (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
		|| (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<'))
		return (0);
	if (str[i] == '<' || str[i] == '>')
	{
		if ((str[i + 1] == ' ' && str[i + 2] == '>')
			|| (str[i + 1] == ' ' && str[i + 2] == '<'))
			return (0);
		while (str[i])
		{
			if (str[i] != ' ' && str[i] != '\t')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

int	valid_input(t_shell *args)
{
	int	i;

	i = 0;
	if (args->input[i] == '|')
		return (0);
	while (args->input[i] == ' ')
		i++;
	while (args->input[i])
	{
		while (ft_isalnum(args->input[i]))
			i++;
		while (args->input[i] == ' ')
			i++;
		if (args->input[i] == ';')
			return (0);
		if (!see_red_closed(args->input, i))
			return (0);
		if (!loop_input(args, &i))
			return (0);
		if (args->input[i] != '\0')
			i++;
	}
	return (1);
}
