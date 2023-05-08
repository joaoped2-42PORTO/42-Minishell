/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:46:04 by huolivei          #+#    #+#             */
/*   Updated: 2023/05/08 14:54:55 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	matrix_cleaner(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
		str[i++] = 0;
}

void	do_loop_new_unset(t_shell *args, int *x, int j, int i)
{
	int	y;

	y = variable_size(args->split[i]);
	if (ft_strncmp(args->new_env[j], args->split[i], y))
	{
		args->env[(*x)++] = ft_strdup(args->new_env[j]);
	}
	else if (!ft_strncmp(args->new_env[j], args->split[i], y))
	{
		args->new_env[j] = 0;
	}
}

void	do_loop_unset(t_shell *args, int *x, int j, int i)
{
	int	y;

	y = variable_size(args->split[i]);
	if (ft_strncmp(args->env[j], args->split[i], y))
	{
		args->new_env[(*x)++] = ft_strdup(args->env[j]);
	}
	else if (!ft_strncmp(args->env[j], args->split[i], y))
	{
		args->env[j] = 0;
	}
}

void	do_unset_new(t_shell *args)
{
	int	i;
	int	j;
	int	x;

	x = 0;
	j = 0;
	i = 0;
	while (args->split[i++])
	{
		if (args->split[i] == 0)
			break ;
		j = 0;
		while (args->new_env[j])
		{
			do_loop_new_unset(args, &x, j, i);
			j++;
		}
	}
	matrix_cleaner(args->new_env);
	args->env[x] = 0;
}

void	do_unset(t_shell *args)
{
	int	i;
	int	j;
	int	x;

	x = 0;
	j = 0;
	i = 0;
	while (args->split[i++])
	{
		if (args->split[i] == 0)
			break ;
		j = 0;
		while (args->env[j])
		{
			do_loop_unset(args, &x, j, i);
			j++;
		}
	}
	matrix_cleaner(args->env);
	args->new_env[x] = 0;
}
