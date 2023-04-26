/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:09:49 by neddy             #+#    #+#             */
/*   Updated: 2023/04/26 14:28:02 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clearcmd(t_shell *args)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execv("/bin/clear", args->split) != 0)
		{
			perror("Error:");
			return ;
		}
	}
	waitpid(-1, NULL, 0);
}
