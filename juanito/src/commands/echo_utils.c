/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:17:17 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/30 11:47:08 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	processdefault(t_shell *args)
{
	int	i;

	i = 1;
	while (args->token->argm[i])
	{
		printf("%s", args->token->argm[i]);
		if (args->token->argm[i + 1])
			printf(" ");
		i++;
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
