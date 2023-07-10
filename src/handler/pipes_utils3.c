/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:44:47 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/10 23:04:37 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	nr_higher(t_shell *args)
{
	g_status = 2;
	printf("%s: %s: numeric argument required\n", args->token->cmd,
		args->token->argm[1]);
	exit(g_status);
}

int	many_args(t_shell *args)
{
	if (args->token->argm[2])
	{
		printf("%s: too many arguments\n", args->token->cmd);
		g_status = 1;
		return (1);
	}
	return (0);
}
