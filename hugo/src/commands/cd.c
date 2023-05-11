/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:27:59 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/11 12:54:36 by huolivei         ###   ########.fr       */
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

void	change_env_pwd(t_shell *args)
{
	int	i;
	char	path[1000];
	char	*str;

	str = "PWD=";
	i = -1;
	getcwd(path, sizeof(path));
	if (args->new_env[0] == 0)
	{
		while (args->env[++i])
		{
			if (!ft_strcmp(args->env[i], "PWD"))
			{
				str = ft_strjoin(str, path);
				args->env[i] = ft_strdup(str);
				free(str);
				break;
			}
		}
	}
	else
	{
		while (args->new_env[++i])
		{
			if (!ft_strcmp(args->new_env[i], "PWD"))
			{
				str = ft_strjoin(str, path);
				args->new_env[i] = ft_strdup(str);
				free(str);
				break;
			}
		}
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
