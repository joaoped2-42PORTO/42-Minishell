/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:03:45 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/15 12:55:32 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*stringtreatment(t_shell *args, char *str, int *k, int *x)
{
	str = malloc((ft_strlen(args->input) + 1) * sizeof(char));
	while (args->split[args->index][*x] != ' '
		&& args->split[args->index][*x] != '\0' && checkisalpha(args, x))
		str[(*k)++] = args->split[args->index][(*x)++];
	str[*k] = '\0';
	return (str);
}

void	process_dollar_sign(t_shell *args, int *x, int *k, char **res)
{
	char	*str;
	char	*ptr2;
	char	*tmp;

	str = NULL;
	ptr2 = NULL;
	tmp = NULL;
	if (args->split[args->index][*x] == '$' && args->split[args->index][*x
		+ 1] != ' ' && args->split[args->index][*x + 1] != '\0'
		&& args->split[args->index][*x + 1] != '$')
	{
		(*x)++;
		str = stringtreatment(args, str, k, x);
		ptr2 = print_env_var(args, str);
		append_ptr2_to_res(res, &ptr2, &tmp);
		free(str);
		*k = 0;
	}
	else
		process_whitespace(args, x, res);
}

void	process_input(t_shell *args, int *x, int *k, char **res)
{
	if (args->split[args->index][*x] == '$' && args->split[args->index][*x
		+ 1] != ' ' && args->split[args->index][*x + 1] != '\0')
		process_dollar_or_char(args, x, k, res);
	else
	{
		while (args->split[args->index][*x] == ' '
			&& args->split[args->index][*x + 1] == ' ')
			(*x)++;
		append_char_to_res(res, args->split[args->index][*x]);
		(*x)++;
	}
}

char	*checkbars(t_shell *args)
{
	int		x;
	int		p;
	int		k;
	int		t;
	char	*res;

	p = 0;
	k = 0;
	t = 0;
	res = calloc(ft_strlen(args->split[args->index]), sizeof(char));
	x = 0;
	while (args->split[args->index][x])
	{
		if ((args->split[args->index][x] == '"' || p % 2 != 0) && t % 2 == 0)
		{
			if (!process_quote(args, &x, &p))
				process_input_condition(args, &x, &k, &res);
		}
		else if ((args->split[args->index][x] == '\'' || t % 2 != 0) && p
				% 2 == 0)
			process_single_quotes(args, &x, &t, &res);
		else
			process_string(args, &x, &res, &k);
	}
	return (res);
}
