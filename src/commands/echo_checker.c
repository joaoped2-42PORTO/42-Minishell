/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:29:07 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/08 17:28:48 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
