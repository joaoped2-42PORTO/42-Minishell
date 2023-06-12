/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:03:45 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/12 14:51:39 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_dollar_sign(t_shell *args, int *x, int *k, char **res)
{
	char	*str;
	char	*ptr2;
	char	*tmp;

	str = NULL;
	ptr2 = NULL;
	tmp = NULL;
	if (args->input[*x] == '$' && args->input[*x + 1] != ' '
		&& args->input[*x + 1] != '\0' && args->input[*x + 1] != '$')
	{
		(*x)++;
		str = malloc((ft_strlen(args->input) + 1) * sizeof(char));
		while (args->input[*x] != ' ' && args->input[*x] != '\0'
			&& checkisalpha(args, x))
			str[(*k)++] = args->input[(*x)++];
		str[*k] = '\0';
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
	if (args->input[*x] == '$' && args->input[*x + 1] != ' '
		&& args->input[*x + 1] != '\0')
		process_dollar_or_char(args, x, k, res);
	else
	{
		while (args->input[*x] == ' ' && args->input[*x + 1] == ' ')
			(*x)++;
		append_char_to_res(res, args->input[*x]);
		(*x)++;
	}
}

char	*checkbars(t_shell *args, int *i)
{
	int		x;
	int		p;
	int		k;
	int		t;
	char	*res;

	p = 0;
	k = 0;
	t = 0;
	res = malloc(1);
	res[0] = '\0';
	x = *i;
	while (args->input[x] && validate_input(args))
	{
		if ((args->input[x] == '"' || p % 2 != 0) && t % 2 == 0)
		{
			if (!process_quote(args, &x, &p))
				process_input_condition(args, &x, &k, &res);
		}
		else if ((args->input[x] == '\'' || t % 2 != 0) && p % 2 == 0)
			process_single_quotes(args, &x, &t, &res);
		else
			process_string(args, &x, &res, &k);
	}
	return (res);
}

int	countvalues(t_shell *args)
{
	int	i;

	i = 0;
	while (args->input[i] == ' ')
		i++;
	while (args->input[i] != ' ' && args->input[i])
		i++;
	while (args->input[i] == ' ')
		i++;
	return (i);
}
