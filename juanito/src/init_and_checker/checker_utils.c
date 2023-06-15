/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:42:10 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/15 14:45:11 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	loop_input(t_shell *args, int *i)
{
	if ((args->input[*i] == '\'' && args->input[*i + 1] == '\'')
		|| (args->input[*i] == '\"' && args->input[*i + 1] == '\"'))
	{
		(*i)++;
		if (!see_quote_double_string(args->input, i))
			return (0);
	}
	else if (args->input[*i] == '\'')
	{
		(*i)++;
		if (!see_quote_string(args->input, i))
			return (0);
	}
	else
	{
		if (!loop_input2(args, i))
			return (0);
		else
			return (1);
	}
	return (1);
}

int	loop_input2(t_shell *args, int *i)
{
	if (args->input[*i] == '\"')
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
