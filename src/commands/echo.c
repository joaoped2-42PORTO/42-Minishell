/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:44:35 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/09 13:58:09 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	suppoptionn(t_shell *args, int *i)
{
	while (1)
	{
		if (!args->split[args->index])
			return (0);
		if (args->index == 1 && checkforbig(args) == 0)
		{
			processdefault(args);
			return (0);
		}
		else if (checkforbig(args) == 0)
			break ;
		else if (checkforbig(args) == 1)
			(*i)++;
		args->index++;
	}
	return (1);
}

void	process_option_n(t_shell *args)
{
	int	i;

	i = 1;
	if (!suppoptionn(args, &i))
		return ;
	if (args->token->argm[i])
	{
		while (args->token->argm[i])
		{
			ft_printf("%s", args->token->argm[i]);
			if (args->token->argm[i + 1])
				ft_printf(" ");
			i++;
		}
	}
}

void	checkcontent(t_shell *args)
{
	int	x;

	x = 0;
	if (!args->token->argm[1])
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
