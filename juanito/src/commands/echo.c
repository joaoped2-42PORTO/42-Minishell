/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:44:35 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/15 14:10:01 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_option_n(t_shell *args)
{
	int	i;

	i = 0;
	if (args->split[args->index][i] == '-' && args->split[args->index][i
		+ 1] == 'n')
	{
		i++;
		while (args->split[args->index][i])
		{
			if (args->split[args->index][i] == '-')
				i++;
			while (args->split[args->index][i] == 'n')
				i++;
			if (args->split[args->index][i] == '\0')
			{
				if (check_index(args, &i) == 0)
					return ;
			}
			else
				if (print_option_n(args) == 0)
					return ;
		}
	}
	processdefault(args);
}

void	checkcontent(t_shell *args)
{
	int	x;

	x = 0;
	if (!args->split[1])
	{
		printf("\n");
		return ;
	}
	args->index = 1;
	if (args->split[args->index][x] == '-' && args->split[args->index][x
		+ 1] == 'n')
		process_option_n(args);
	else
		processdefault(args);
}

void	do_echo(t_shell *args)
{
	checkcontent(args);
}
