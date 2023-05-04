/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:27:59 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/04 12:19:05 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_homedk(t_shell *args)
{
	int		i;
	char	*path;

	i = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->env[i], "HOME=", 5))
		{
			path = args->env[i] + 5;
			chdir(path);
			return ;
		}
		i++;
	}
}

void	ft_olddk(t_shell *args)
{
	int		i;
	char	*path;

	i = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->env[i], "OLDPWD=", 7))
		{
			path = args->env[i] + 7;
			change_env_oldpwd(args);
			chdir(path);
			return ;
		}
		i++;
	}
}

void	do_cd(t_shell *args)
{
	int		error;

	error = 0;
	if (!args->split[1])
	{
		change_env_oldpwd(args);
		ft_homedk(args);
		change_env_pwd(args);
		return ;
	}
	else if (args->split[1][0] == '-')
	{
		ft_olddk(args);
		change_env_pwd(args);
		return ;
	}
	change_env_oldpwd(args);
	error = chdir(args->split[1]);
	if (error != 0)
	{
		perror("Error");
		return ;
	}
	change_env_pwd(args);
}

void	change_env_pwd(t_shell *args)
{
	int		i;
	char	path[1000];
	char	*str;

	str = "PWD=";
	i = -1;
	getcwd(path, sizeof(path));
	while (args->env[++i])
	{
		if (!ft_strcmp(args->env[i], "PWD"))
		{
			str = ft_strjoin(str, path);
			args->env[i] = ft_strdup(str);
			break ;
		}
	}
	free(str);
}

void	change_env_oldpwd(t_shell *args)
{
	int		i;
	char	path[1000];
	char	*str;

	str = "OLDPWD=";
	i = -1;
	getcwd(path, sizeof(path));
	while (args->env[++i])
	{
		if (!ft_strcmp(args->env[i], "OLDPWD"))
		{
			str = ft_strjoin(str, path);
			args->env[i] = ft_strdup(str);
			break ;
		}
	}
	free(str);
}
