/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:27:59 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/24 17:53:09 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_cd(t_shell *args)
{
	int		error;

	error = 0;
	if (!args->split[1])
	{
		chdir(getenv("HOME"));
		return ;
	}
	else if (args->split[1][0] == '-')
	{
		chdir(getenv("OLDPWD"));
		return ;
	}
	error = chdir(args->split[1]);
	if (error != 0)
		printf("Wrong directory!\n");
}
