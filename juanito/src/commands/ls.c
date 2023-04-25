/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neddy <neddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:10:45 by neddy             #+#    #+#             */
/*   Updated: 2023/04/25 11:11:04 by neddy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lscmd(t_shell *args)
{
	int	pid;

	if ((pid = fork()) == 0)
	{
    		if(execv("/bin/ls", args->split) != 0)
			{
				perror("Error:");
				return ;
			}
	}
	waitpid(-1, NULL, 0);
}
