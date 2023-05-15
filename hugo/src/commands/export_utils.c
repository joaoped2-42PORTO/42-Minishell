/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:05:06 by huolivei          #+#    #+#             */
/*   Updated: 2023/05/15 12:10:39 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_loop_new_doubles(t_shell *args, int j)
{
	int	i;

	i = 0;
	while (args->new_env[i])
	{
		if (!ft_strncmp(args->split[j], args->new_env[i], variable_size(args->new_env[i])))
					return (0);
		i++;
	}
	return (1);
}

int	do_loop_doubles(t_shell *args, int j)
{
	int	i;

	i = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->split[j], args->env[i], variable_size(args->env[i])))
					return (0);
		i++;
	}
	return (1);
}

int	check_doubles_vars(t_shell *args)
{
	int	j;

	j = 0;
	if (args->new_env[0] == 0)
	{
		while (args->split[j])
		{
			if(!do_loop_doubles(args, j))
				return (0);
			j++;
		}
	}
	else
	{
		while (args->split[j])
		{
			if (!do_loop_new_doubles(args, j))
				return (0);
			j++;
		}
	}
	return (1);
}

int	see_env_size(t_shell *args)
{
	int	i;

	i = 0;
	if (args->new_env[0] == 0)
	{
		while (args->env[i])
			i++;
		//args->env[i] = malloc(sizeof(char) * (ft_strlen(args->input)));
	}
	else
	{
		while (args->new_env[i])
			i++;
		//args->new_env[i] = malloc(sizeof(char) * (ft_strlen(args->input)));
	}
	return (i);
}

void	single_export(t_shell *args, int *j, int *x, int *i)
{
	args->env[*i] = ft_calloc(ft_strlen(args->input), sizeof(char));
	while (args->input[*j])
	{
		if (args->input[*j] == '"')
			(*j)++;
		if (args->new_env[0] != 0)
			args->new_env[*i][(*x)++] = args->input[(*j)++];
		else
			args->env[*i][(*x)++] = args->input[(*j)++];
	}
	args->env[*i][*x] = '\0';
}
