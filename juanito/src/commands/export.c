/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:38:03 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/15 14:56:40 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	see_if_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	see_exp_size(t_shell *args)
{
	int	i;

	i = 0;
	while (args->exp[i])
		i++;
	return (i);
}

void	mult_free_final(char **env, char **exp)
{
	free_matrix(env);
	free_matrix(exp);
}

void	mult_change_vals(t_shell *args, int *x, int *i)
{
	args->env[*i] = 0;
	args->exp[*x] = 0;
}

void	do_mult_export(t_shell *args)
{
	int		i;
	int		x;
	int		y;
	char	**env;
	char	**exp;

	y = 0;
	args->flag = 0;
	x = see_exp_size(args);
	i = see_env_size(args);
	env = ft_calloc(i + 1, sizeof(char *));
	exp = ft_calloc(x + 1, sizeof(char *));
	exchange_memo(args, env, exp, &i, &x);
	while (args->split[++y])
	{
		if (!see_if_env(args->split[y]))
			args->exp[x++] = ft_strdup(args->split[y]);
		else
		{
			args->env[i++] = ft_strdup(args->split[y]);
			args->exp[x++] = ft_strdup(args->split[y]);
		}
	}
	mult_free_final(env, exp);
	mult_change_vals(args, &x, &i);
}
