/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:34:28 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/05 10:30:40 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	newenvmalloc(t_shell *args, int y, int i)
{
	if (args->input[y] != '\0')
		args->new_env[i] = malloc(sizeof(char) * (ft_strlen(args->input) - y));
}

void	exphelper(t_shell *args, int i, int x, int y)
{
	int	flag;

	flag = 0;
	while (args->input[y++])
	{
		checkermultexp2(args, flag, y);
		if (flag % 2 == 0 && flag != 0)
		{
			args->new_env[i][x] = '\0';
			i++;
			y++;
			newenvmalloc(args, y, i);
			x = 0;
			flag = 0;
		}
		args->new_env[i][x] = args->input[y];
		x++;
	}
	args->new_env[i] = 0;
}

void	mult_export_new(t_shell *args)
{
	int	i;
	int	x;
	int	y;

	y = 6;
	x = 0;
	i = 0;
	exphelper(args, i, x, y);
}

int	checker(t_shell *args)
{
	if (args->split[1] == 0)
	{
		print_export(args);
		return (1);
	}
	else if (args->split[2] != 0)
	{
		do_mult_export(args);
		return (0);
	}
	else
		return (0);
}

void	do_export(t_shell *args)
{
	int	i;
	int	j;
	int	x;

	x = 0;
	j = 7;
	if (checker(args) == 1)
		return ;
	i = see_env_size(args);
	while (args->input[j])
	{
		if (args->input[j] == '"')
			j++;
		if (args->new_env[0] != 0)
			args->new_env[i][x++] = args->input[j++];
		else
			args->env[i][x++] = args->input[j++];
	}
	args->env[i][x] = '\0';
	i++;
	args->env[i] = 0;
}
