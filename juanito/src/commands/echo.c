/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:44:35 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/29 15:46:10 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checksplitcontent(t_shell *args)
{
	int	i;

	i = 0;
	while (args->split[1][i])
		i++;
	return (i);
}


void	do_echo(t_shell *args)
{
	int	i;

	checksplitcontent(args);
	i = countvalues(args);
	if (!args->split[1])
		printf("\n");
	else if (checksplitcontent(args) == 2)
		printf("%s", checkbars(args, &i));
	else
		printf("%s\n", checkbars(args, &i));
}
