/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:35:20 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/27 16:05:41 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	nonb(t_shell *args)
{
	int		pid;
	char	path[6]= "/bin/";
	char	*res = NULL;

	res = ft_strcat(path, args->split[1]);
	pid = fork();
	if (pid == 0)
	{
		if (execv(res, args->split) != 0)
		{
			perror("Error:");
			return ;
		}
	}
	waitpid(-1, NULL, 0);
}
