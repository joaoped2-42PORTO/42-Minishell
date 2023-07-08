/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:17:17 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/08 17:28:48 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	checkforbig(t_shell *args)
{
	int	i;

	i = 0;
	while (args->split[args->index][i])
	{
		if (args->split[args->index][i] == '-')
			i++;
		while (args->split[args->index][i] == 'n')
			i++;
		if (args->split[args->index][i] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}
