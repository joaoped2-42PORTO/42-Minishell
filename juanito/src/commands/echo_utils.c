/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:17:17 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/15 12:48:25 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	processdefault(t_shell *args)
{
	while (args->split[args->index])
	{
		printf("%s", args->split[args->index]);
		if (args->split[args->index])
		{
			printf(" ");
			args->index++;
		}
	}
	printf("\n");
}

int	print_option_n(t_shell *args)
{
	while (args->split[args->index])
	{
		if (args->index == 1)
			return (0);
		else
			printf("%s", args->split[args->index]);
		args->index++;
		if (args->split[args->index])
			printf(" ");
		else
			return (0);
	}
	return (1);
}

int	check_index(t_shell *args, int *i)
{
	if (!args->split[args->index + 1])
		return (0);
	args->index++;
	if (!args->split[args->index])
		return (0);
	*i = 0;
	return (1);
}
