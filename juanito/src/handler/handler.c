/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/26 17:01:46 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmdhandler(t_shell *args)
{
	int i = 0;
	if (!ft_strncmp(args->split[0], "pwd", 3))
		check_pwd();
	else if (!ft_strncmp(args->split[0], "cd", 2))
		do_cd(args);
	else if (!ft_strncmp(args->split[0], "env", 3))
		print_env(args);
	else if (!ft_strncmp(args->split[0], "exit", 4))
		return (0);
	else if (!ft_strncmp(args->split[0], "clear", 5))
		clearcmd(args);
	else if (!ft_strncmp(args->split[0], "ls ", 2))
		lscmd(args);
	else if (!ft_strncmp(args->split[0], "export", 6))
		ft_export(args);
	else if (!ft_strncmp(args->split[0], "test", 4))
	{
		while (args->var[++i])
			printf("Test Command: %s\n", args->var[i]);
	}
	else
		printf("command not found: %s\n", args->input);
	return (1);
}
