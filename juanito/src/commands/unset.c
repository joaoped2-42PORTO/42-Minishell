/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:45:02 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/08 12:05:02 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	smallfc(t_shell *args, int j, int i)
{
	int	k;

	if (args->env[0] != 0)
		k = ft_strncmp(args->env[j], args->split[i], ft_strlen(args->env[i]));
	else
		k = ft_strncmp(args->new_env[j], args->split[i], ft_strlen(args->new_env[i]));
	return (k);
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
			if (smallfc(args, j, i))
				args->new_env[x++] = ft_strdup(args->env[j]);
			else if (!smallfc(args, j, i))
				args->env[j] = 0;
			j++;
		}
	}
	matrix_cleaner(args->env);
	args->new_env[x] = 0;
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
			if (smallfc(args, j, i))
				args->env[x++] = ft_strdup(args->new_env[j]);
			else if (!smallfc(args, j, i))
				args->new_env[j] = 0;
			j++;
		}
	}
	matrix_cleaner(args->new_env);
	args->env[x] = 0;
}

void	matrix_cleaner(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
		str[i++] = 0;
}
