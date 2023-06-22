/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:27:59 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/22 23:11:29 by huolivei         ###   ########.fr       */
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

void	change_env_pwd(t_shell *args)
{
	int	i;
	char	path[1000];
	char	*str;

	str = "PWD=";
	i = -1;
	getcwd(path, sizeof(path));
	while (args->env[++i])
	{
		if (!ft_strcmp(args->env[i], "PWD"))
		{
			if (args->path != NULL)
				free(args->path);
			str = ft_strjoin(str, path);
			free(args->env[i]);
			args->env[i] = ft_strdup(str);
			args->path = ft_strdup(str);
			free(str);
			break;
		}
	}
}

void	change_exp_pwd(t_shell *args)
{
	int	i;
	char	path[1000];
	char	*str;

	str = "PWD=";
	i = -1;
	getcwd(path, sizeof(path));
	while (args->exp[++i])
	{
		if (!ft_strcmp(args->exp[i], "PWD"))
		{
			str = ft_strjoin(str, path);
			free(args->exp[i]);
			args->exp[i] = ft_strdup(str);
			free(str);
			break;
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
		change_exp_pwd(args);
		return ;
	}
	change_env_oldpwd(args);
	error = chdir(args->split[1]);
	if (error != 0)
	{
		perror("Error");
		args->exit_status = 1;
		return ;
	}
	change_env_pwd(args);
	change_exp_pwd(args);
	args->exit_status = 0;
}
