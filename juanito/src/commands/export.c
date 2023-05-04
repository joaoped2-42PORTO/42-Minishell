/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:44:55 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/04 14:52:15 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	checkermultexp(t_shell *args)
{
	if (args->new_env[0] != 0)
	{
		mult_export_new(args);
		return ;
	}
}

void	checkermultexp2(t_shell *args, int flag, int y)
{
	if (args->input[y] == '"')
	{
		flag++;
		y++;
	}
}

void	tiredofpoopo(t_shell *args, int i, int x, int y)
{
	args->env[i][x] = '\0';
	i++;
	y++;
}

void	cleanxandflag(int x, int flag)
{
	x = 0;
	flag = 0;
}

void	do_mult_export(t_shell *args)
{
	int	i;
	int	x;
	int	flag;
	int	y;

	y = 6;
	flag = 0;
	x = 0;
	i = see_env_size(args);
	checkermultexp(args);
	while (args->input[y++])
	{
		checkermultexp2(args, flag, y);
		if (args->input[y] == '\0')
			break ;
		if (flag % 2 == 0 && flag != 0)
		{
			tiredofpoopo(args, i, x, y);
			newenvmalloc(args, y, i);
			cleanxandflag(x, flag);
		}
		else
			args->env[i][x++] = args->input[y];
	}
	args->env[i] = 0;
}
