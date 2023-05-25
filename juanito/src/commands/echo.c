/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:44:35 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/25 15:40:28 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echonoflags(t_shell *args)
{
	int	i;
	int	x;

	i = 5;
	if (string(args, &i) == 1)
	{
		i = countvalues(args);
		printf("%s", checkbars(args, &i));
	}
	if (isdollar(args) == 0)
		printf("\n");
	else
	{
		treatingdollarsign(args, &i);
		x = checkafterdollar(args);
		getindexafterdollar(args, &x);
		printf("\n");
	}
}

void	do_echo(t_shell *args)
{
	int	i;

	if (!args->split[1])
		printf("\n");
	else if (!ft_strncmp(args->split[1], "-n", 2))
	{
		if (!args->split[2])
			return ;
		i = countvalues(args);
		if (isdollar(args) == 0)
			printf("%s", checkbars(args, &i));
	}
	else
		echonoflags(args);
}

