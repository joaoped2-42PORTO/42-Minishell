/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:38:03 by huolivei          #+#    #+#             */
/*   Updated: 2023/07/13 20:36:34 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_export(t_shell *args)
{
	if (args->split[1] == 0)
	{
		print_export(args);
		g_status = 0;
		return ;
	}
	do_mult_export(args);
}

int	check_env_value(t_shell *args, char *str)
{
	int	i;

	i = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->env[i], str, variable_size(args->env[i])))
			return (i);
		i++;
	}
	return (0);
}

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

void	do_mult_export(t_shell *args)
{
	int		i;
	int		x;
	char	**env;
	char	**exp;

	x = see_exp_size(args);
	i = see_env_size(args);
	env = ft_calloc(i + 1, sizeof(char *));
	exp = ft_calloc(x + 1, sizeof(char *));
	exchange_memo_env(args, env, &i);
	exchange_memo_exp(args, exp, &x);
	export_counting(args, &x, &i);
	free_matrix(env);
	free_matrix(exp);
	args->env[i] = 0;
	args->exp[x] = 0;
}
