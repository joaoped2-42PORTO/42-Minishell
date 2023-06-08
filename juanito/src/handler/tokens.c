/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:22:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/08 14:55:37 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checkisalpha(t_shell *args, int *i)
{
	int	x;

	x = *i;
	if (args->input[x] >= 48 && args->input[x] <= 57)
		return (1);
	else if (args->input[x] >= 65 && args->input[x] <= 90)
		return (1);
	else if (args->input[x] >= 97 && args->input[x] <= 122)
		return (1);
	return (0);
}

void	append_char_to_res(char **res, char c)
{
	char	*ptr;
	char	*tmp;

	ptr = (char *)malloc(2 * sizeof(char));
	ptr[0] = c;
	ptr[1] = '\0';
	tmp = malloc(ft_strlen(*res) + ft_strlen(ptr) + 1);
	strcpy(tmp, *res);
	strcat(tmp, ptr);
	free(*res);
	*res = tmp;
	free(ptr);
}

void	process_whitespace(t_shell *args, int *x, char **res)
{
	while (args->input[*x] == ' ' && args->input[*x + 1] == ' ')
		(*x)++;
	append_char_to_res(res, args->input[(*x)++]);
}

void	append_ptr2_to_res(char **res, char **ptr2, char **tmp)
{
	if (*ptr2)
	{
		*tmp = malloc(ft_strlen(*res) + ft_strlen(*ptr2) + 1);
		strcpy(*tmp, *res);
		strcat(*tmp, *ptr2);
		free(*res);
		*res = *tmp;
		free(*ptr2);
	}
}

void	process_single_quotes(t_shell *args, int *x, int *t, char **res)
{
	if (args->input[*x] == '\'')
	{
		(*x)++;
		(*t)++;
	}
	else
		append_char_to_res(res, args->input[(*x)++]);
}

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

void	process_quote(int *x, int *p)
{
	(*x)++;
	(*p)++;
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
		process_quote(x, NULL);
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

int	handle_quotes(t_shell *args, int *x, int *p, char **res)
{
	if (args->input[*x] == '"')
	{
		(*x)++;
		(*p)++;
		return (1);
	}
	else if (args->input[*x] == '$' && args->input[*x + 1] != ' '
		&& args->input[*x + 1] != '\0')
	{
		process_dollar_or_char(args, x, p, res);
		return (1);
	}
	else
	{
		append_char_to_res(res, args->input[*x]);
		(*x)++;
		return (0);
	}
}

int	handle_single_quotes(t_shell *args, int *x, int *t)
{
	if (args->input[*x] == '\'')
	{
		(*x)++;
		(*t)++;
		return (1);
	}
	else
		return (0);
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
			process_quote(&x, &p);
		else if ((args->input[x] == '\'' || t % 2 != 0) && p % 2 == 0)
			process_single_quotes(args, &x, &t, &res);
		else if (p % 2 == 0)
			process_input_condition(args, &x, &k, &res);
		else
			append_char_to_res(&res, args->input[x++]);
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
