/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:10:45 by neddy             #+#    #+#             */
/*   Updated: 2023/04/26 14:28:23 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lscmd(t_shell *args)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execv("/bin/ls", args->split) != 0)
		{
			perror("Error:");
			return ;
		}
	}
	waitpid(-1, NULL, 0);
}
