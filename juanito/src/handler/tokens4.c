/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:04:15 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/03 17:05:00 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checkfortabs(t_shell *args, int *x)
{
	if (args->split[args->index][*x] == '\t' && args->split[args->index][(*x)
		+ 1] != '\t' && args->split[args->index][(*x) + 1] != ' '
		&& args->split[args->index][(*x) + 1] != '\0')
		args->split[args->index][*x] = ' ';
	else if (args->split[args->index][*x] == '\t'
		&& args->split[args->index][(*x) + 1] == '\t')
		(*x)++;
	else if (args->split[args->index][*x] == '\t'
		&& args->split[args->index][(*x) + 1] == ' ')
		(*x)++;
	else if (args->split[args->index][*x] == '\t')
		(*x)++;
	else
		return (0);
	return (1);
}
