/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:44:35 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/23 16:19:45 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echonoflags(t_shell *args)
{
	//char	*src = NULL;
	int		i;

	i = 0;
	countvalues(args);
	printf("%s", checkbars(args, &i));
	printf("\n");
}

void	do_echo(t_shell *args)
{
	if (!args->split[1])
		printf("\n");
	else if (!ft_strncmp(args->split[1], "-n", 2))
		countvalues(args);
	else
		echonoflags(args);
}

