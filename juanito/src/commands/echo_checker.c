/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:29:07 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/07 14:57:59 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checkforspacesinstring(t_shell *args, int i)
{
	int	j;

	j = 0;
	if (!args->input[i])
		return (0);
	while (args->input[i])
	{
		while (args->input[i] != ' ' && args->input[i])
			i++;
		while (args->input[i] == ' ' && args->input[i])
		{
			j++;
			i++;
		}
		return (j);
		i++;
	}
	return (j);
}

int	isdoublequote(t_shell *args)
{
	int	i;

	i = 0;
	while (args->input[i])
	{
		if (args->input[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

void	print_processed_result(t_shell *args, char *res)
{
	int	k;

	k = 0;
	while (res[k])
	{
		if (isdoublequote(args) != 0)
		{
			printf("%s", res);
			break ;
		}
		if (res[k] == ' ' && res[k + 1] == ' ')
			k++;
		else if (res[k] == ' ' && k == 0)
			k++;
		else
			write(1, &res[k++], 1);
	}
	printf("\n");
}
