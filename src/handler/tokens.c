/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:22:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/23 15:25:30 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_quote(t_shell *args, int *x, int *p)
{
	if (args->split[args->index][*x] == '"')
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
	char	*str;
	size_t	i;

	i = 0;
	if (args->split[args->index][*x] == '$')
	{
		if (args->split[args->index][*x + 1] == '?')
		{
			(*x) += 2;
			str = ft_itoa(g_status);
			while (i < ft_strlen(str))
				append_char_to_res(res, str[(i)++]);
			free(str);
		}
		else if ((args->split[args->index][*x + 1] != ' '
			|| args->split[args->index][*x + 1] != '\t')
			&& args->split[args->index][*x + 1] != '\0')
			process_dollar_sign(args, x, k, res);
		else
			append_char_to_res(res, args->split[args->index][(*x)++]);
	}
	else
		append_char_to_res(res, args->split[args->index][(*x)++]);
}

void	process_input_condition(t_shell *args, int *x, int *k, char **res)
{
	if (args->split[args->index][*x] == '"')
		process_quote(args, x, NULL);
	else if (args->split[args->index][*x] == '$')
		process_dollar_or_char(args, x, k, res);
	else
		append_char_to_res(res, args->split[args->index][(*x)++]);
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
	while (args->split[args->index][*x] != '\''
		&& args->split[args->index][*x] != '"' && args->split[args->index][*x])
	{
		if ((args->split[args->index][*x] == ' '
			&& args->split[args->index][(*x) + 1] == ' '))
			(*x)++;
		else if (args->split[args->index][*x] == '$')
			process_dollar_or_char(args, x, k, res);
		else
			append_char_to_res(res, args->split[args->index][(*x)++]);
	}
}
