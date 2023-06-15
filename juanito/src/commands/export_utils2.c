/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:06:30 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/15 15:29:22 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_loop_doubles(t_shell *args, int j)
{
	int	i;

	i = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->split[j], args->env[i],
				variable_size(args->env[i])))
			return (0);
		i++;
	}
	return (1);
}

int	check_doubles_vars(t_shell *args)
{
	int	j;

	j = 0;
	while (args->split[j])
	{
		if (!do_loop_doubles(args, j))
			return (0);
		j++;
	}
	return (1);
}

void	exchange_memo_env(t_shell *args, char **env, int *i)
{
	env = dup_env(args->env, env);
	free_matrix(args->env);
	args->env = ft_calloc(*i + see_split_size(args), sizeof(char *));
	args->env = dup_env(env, args->env);
}

void	exchange_memo_exp(t_shell *args, char **exp, int *x)
{
	exp = dup_env(args->exp, exp);
	free_matrix(args->exp);
	args->exp = ft_calloc(*x + see_split_size(args), sizeof(char *));
	args->exp = dup_env(exp, args->exp);
}

void	export_counting(t_shell *args, int *x, int *i)
{
	int	y;

	y = 0;
	while (args->split[++y])
	{
		if (!see_if_env(args->split[y]))
			args->exp[(*x)++] = ft_strdup(args->split[y]);
		else
		{
			args->env[(*i)++] = ft_strdup(args->split[y]);
			args->exp[(*x)++] = ft_strdup(args->split[y]);
		}
	}
}
