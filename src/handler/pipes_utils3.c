/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neddy <neddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:44:47 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/11 16:15:40 by neddy            ###   ########.fr       */
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

void	nr_higher_pipes(t_shell *args)
{
	g_status = 2;
	printf("%s: %s: numeric argument required\n", args->token->cmd,
		args->token->argm[1]);
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
