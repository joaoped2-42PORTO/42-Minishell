/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:03:45 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/20 10:05:12 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_extractvalue(const char *string, const char *variable)
{
	size_t		var_len;
	const char	*start;
	const char	*end;
	size_t		len;
	char		*value;

	var_len = ft_strlen(variable);
	start = ft_strstr(string, variable);
	if (start != NULL && *(start + var_len) == '=')
	{
		end = ft_strchr(start, ' ');
		if (end == NULL)
		{
			end = start + ft_strlen(start);
		}
		len = end - (start + var_len + 1);
		value = malloc((len + 1) * sizeof(char));
		if (value != NULL)
		{
			ft_strncpy(value, start + var_len + 1, len);
			value[len] = '\0';
			return (value);
		}
	}
	return (NULL);
}

char	*getvalue(const char *string1, const char *string2)
{
	const char	*delim;
	char		*var;

	delim = "$";
	var = strstr(string2, delim);
	if (var != NULL)
	{
		var += ft_strlen(delim);
		return (ft_extractvalue(string1, var));
	}
	return (NULL);
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
		str = helpdollarsign(args, x, k, str);
		if (!help_dollar_sign2(args, x, res, str))
			return ;
		ptr2 = help_dollar_sign3(args, ptr2, str);
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
			|| args->split[args->index][*x + 1] == ' '
			|| args->split[args->index][*x + 1] == '\t'
			|| args->split[args->index][*x] == '\t')
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
	res = ft_calloc(ft_strlen(args->split[args->index]) + 1, sizeof(char));
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
