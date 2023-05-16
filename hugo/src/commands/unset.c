/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:46:04 by huolivei          #+#    #+#             */
/*   Updated: 2023/05/16 23:49:39 by huolivei         ###   ########.fr       */
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

int	string_comp(char *str, char *str1)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (str1[j])
	{
		j++;
		if (str1[j] == '=')
			break ;
	}
	return (i - j);
}

void	do_loop_new_unset(t_shell *args, int *x, int j, int i)
{
	if (string_comp(args->split[i], args->new_env[j]))
		args->env[(*x)++] = ft_strdup(args->new_env[j]);
}

void	do_loop_unset(t_shell *args, int *x, int j, int i)
{
	if (string_comp(args->split[i], args->env[j]))
		args->new_env[(*x)++] = ft_strdup(args->env[j]);
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
	x++;
	args->new_env[x] = 0;
}
