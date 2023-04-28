/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:35:20 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/28 10:12:53 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	nonb(t_shell *args)
{
	int		pid;
	char	path[6]= "/bin/";
	char	*res = NULL;

	res = ft_strcat(path, argcount(args));
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

void	argcount(t_shell *args)
{
	int	i;

	i = 0;
	while (args->split[i])
	{
		if (!strncmp(args->split[i], "cat", 3))
			nonb(args);
		else if (!strncmp(args->split[i], "grep", 4))
			nonb(args);
		else if (!strncmp(args->split[i], "which", 5))
			nonb(args);
		i++;
	}
}
