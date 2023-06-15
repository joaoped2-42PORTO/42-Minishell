/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:14:26 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/15 14:48:15 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executepid(t_shell *args)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (args->input[0] == '.' && args->input[1] == '/')
		open_exec(args);
	else if (args->input[0] == '/')
		open_exec_abs(args);
}

char	*getthepath(t_shell *args)
{
	char	*path;
	char	**path_split;

	path = get_path(args);
	if (path)
	{
		path_split = ft_split(path, ':');
		free (path);
		path = get_acess(path_split, args);
		return (path);
	}
	else
	{
		free (path);
		return (0);
	}
}

void	open_exec_helper(t_shell *args, char *str)
{
	if (execve(str, args->split, NULL) != 0)
	{
		perror("Error");
		free(str);
		args->exit_status = 126;
		exit(126);
	}
}
