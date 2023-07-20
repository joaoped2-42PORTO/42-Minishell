/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:04:13 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/20 10:05:15 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*helpdollarsign(t_shell *args, int *x, int *k, char *str)
{
	str = malloc((ft_strlen(args->input) + 1) * sizeof(char));
	while (args->split[args->index][*x] != ' '
		&& args->split[args->index][*x] != '\0' && checkisalpha(args, x))
		str[(*k)++] = args->split[args->index][(*x)++];
	str[*k] = '\0';
	return (str);
}

int	help_dollar_sign2(t_shell *args, int *x, char **res, char *str)
{
	if (args->index != 0)
	{
		if (args->split[args->index - 1][0] == '<' && args->split[args->index
			- 1][1] == '<')
		{
			(*x) = 0;
			while (args->split[args->index][*x])
				append_char_to_res(res, args->split[args->index][(*x)++]);
			free (str);
			return (0);
		}
	}
	return (1);
}

char	*help_dollar_sign3(t_shell *args, char *ptr2, char *str)
{
	if (args->index >= 1)
		ptr2 = getvalue(args->split[args->index - 1], args->split[args->index]);
	if (!ptr2)
		ptr2 = print_env_var(args, str);
	return (ptr2);
}
