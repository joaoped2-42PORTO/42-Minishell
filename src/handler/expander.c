/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:30:01 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/10 12:52:52 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_dollar_sign1(t_shell *args, char *str, int *x, char **res)
{
	char	*ptr;
	char	*ptr2;
	char	*tmp;
	int		k;

	k = 0;
	ptr = NULL;
	ptr2 = NULL;
	tmp = NULL;
	if (checkdollar(str, x))
	{
		(*x)++;
		if (str[*x] >= 48 && str[*x] <= 57)
			checkisnumonfirst(str, x, res);
		ptr = malloc((ft_strlen(args->input) + 1) * sizeof(char));
		while (str[*x] != ' ' && str[*x] != '\0' && !ft_isprintable(str[*x]))
			ptr[(k)++] = str[(*x)++];
		ptr[k] = '\0';
		ptr2 = print_env_var(args, ptr);
		free(ptr);
		append_ptr2_to_res1(res, &ptr2, &tmp);
		k = 0;
	}
	else
		append_char_to_res1(res, str[(*x)++]);
}

void	process_dollar_or_char1(t_shell *args, char *str, int *x, char **res)
{
	char	*ptr;

	if (str[*x] == '$')
	{
		if (str[*x + 1] == '?')
		{
			ptr = ft_itoa(g_status);
			ft_strcat(*res, ptr);
			free(ptr);
			(*x) += 2;
		}
		else
			process_dollar_sign1(args, str, x, res);
	}
	else
		append_char_to_res1(res, str[(*x)++]);
}

void	process_string1(t_shell *args, char *str, int *x, char **res)
{
	if (str[*x] == '$' && str[*x])
		process_dollar_or_char1(args, str, x, res);
	else
		append_char_to_res1(res, str[(*x)++]);
}

char	*print_env_var2(t_shell *args, char *str)
{
	int		x;
	char	*res;

	res = ft_calloc(ft_strlen(str), sizeof(char));
	x = 0;
	while (str[x])
		process_string1(args, str, &x, &res);
	return (res);
}
