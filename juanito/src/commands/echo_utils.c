/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:17:17 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/14 16:40:17 by joaoped2         ###   ########.fr       */
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

void	print_option_n(t_shell *args)
{
	while (args->split[args->index])
	{
		printf("%s", args->split[args->index]);
		args->index++;
		if (args->split[args->index])
			printf(" ");
		return ;
	}
}

void	check_index(t_shell *args, int *i)
{
	if (!args->split[args->index + 1])
		return ;
	args->index++;
	*i = 0;
}
