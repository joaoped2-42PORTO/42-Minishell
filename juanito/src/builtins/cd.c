/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neddy <neddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:27:59 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/27 14:16:29 by neddy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_cd(t_shell *args)
{
	int		error;

	error = 0;
	if (!args->split[1])
	{
		ft_homedk(args);
		return ;
	}
	else if (args->split[1][0] == '-')
	{
		ft_homedk(args);
		return ;
	}
	error = chdir(args->split[1]);
	if (error != 0)
		printf("Wrong directory!\n");
}


void	ft_homedk(t_shell *args)
{
	int		i;
	char	*path = NULL;
	char	pwd[1000];

	getcwd(pwd, sizeof(pwd));

	i = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->env[i], "HOME=", 5))
			path = args->env[i] + 5;
		else if (!ft_strncmp(args->env[i], "OLDPWD=", 7))
			path = args->env[i] + 7;
		i++;
	}
	chdir(path);
}
