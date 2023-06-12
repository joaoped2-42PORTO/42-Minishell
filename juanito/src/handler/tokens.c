/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:22:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/12 14:30:49 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_quote(t_shell *args, int *x, int *p)
{
	if (args->input[*x] == '"')
	{
		(*x)++;
		(*p)++;
		return (1);
	}
	else
		return (0);
}

void	process_dollar_or_char(t_shell *args, int *x, int *k, char **res)
{
	if (args->input[*x] == '$')
	{
		if (args->input[*x + 1] != ' ' && args->input[*x + 1] != '\0')
			process_dollar_sign(args, x, k, res);
		else
			append_char_to_res(res, args->input[(*x)++]);
	}
	else
		append_char_to_res(res, args->input[(*x)++]);
}

void	process_input_condition(t_shell *args, int *x, int *k, char **res)
{
	if (args->input[*x] == '"')
		process_quote(args, x, NULL);
	else if (args->input[*x] == '$')
		process_dollar_or_char(args, x, k, res);
	else
		append_char_to_res(res, args->input[(*x)++]);
}

int	validate_input(t_shell *args)
{
	if (valid_input(args) == 0)
	{
		printf("Error");
		return (0);
	}
	return (1);
}

void	process_string(t_shell *args, int *x, char **res, int *k)
{
	while (args->input[*x] != '\'' && args->input[*x] != '"' && args->input[*x])
	{
		if (args->input[*x] == ' ' && args->input[(*x) + 1] == ' ')
			(*x)++;
		else if (args->input[*x] == '$')
			process_dollar_or_char(args, x, k, res);
		else
			append_char_to_res(res, args->input[(*x)++]);
	}
}
