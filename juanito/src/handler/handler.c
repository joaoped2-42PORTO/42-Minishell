/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/04 13:10:32 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_builtins(t_shell *args)
{
	int		pid;
	char	*path;
	char	*res;

	path = "/usr/bin/";
	res = ft_strjoin(path, args->split[0]);
	pid = fork();
	if (pid == 0)
	{
		if (execv(res, args->split) != 0)
		{
			printf("command not found: %s\n", args->input);
			exit (1);
		}
	}
	waitpid(-1, NULL, 0);
	free(res);
	return (1);
}

int	cmdhandler(t_shell *args)
{
	if (args->input[0] == '\0')
		return (1);
	else if (!ft_strncmp(args->split[0], "pwd", 3))
		check_pwd();
	else if (!ft_strncmp(args->split[0], "cd", 2))
		do_cd(args);
	else if (!ft_strncmp(args->split[0], "env", 3))
		print_env(args);
	else if (!ft_strncmp(args->split[0], "exit", 4))
		return (0);
	else if (!ft_strncmp(args->split[0], "echo", 4))
		do_echo(args);
	else if (!ft_strncmp(args->split[0], "export", 6))
		do_export(args);
	else if (!ft_strncmp(args->split[0], "unset", 5))
	{
		if (args->new_env[0] == 0)
			do_unset(args);
		else
			do_unset_new(args);
	}
	else if (do_builtins(args) == 1)
		return (1);
	return (1);
}
