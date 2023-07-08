/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:27:59 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/08 23:19:30 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_homedk(t_shell *args)
{
	int		i;
	char	*path;

	i = 0;
	while (args->env[i])
	{
		if (var_is_equal(args->env[i], "HOME"))
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
	int		i;
	char	path[1000];
	char	*str;

	str = "PWD=";
	i = -1;
	getcwd(path, sizeof(path));
	while (args->env[++i])
	{
		if (var_is_equal(args->env[i], "PWD"))
		{
			if (args->path != NULL)
				free(args->path);
			str = ft_strjoin(str, path);
			free(args->env[i]);
			args->env[i] = ft_strdup(str);
			args->path = ft_strdup(str);
			free(str);
			return ;
		}
	}
	args->env[i] = ft_strjoin(str, path);
}

void	change_exp_pwd(t_shell *args)
{
	int		i;
	char	path[1000];
	char	*str;

	str = "PWD=";
	i = -1;
	getcwd(path, sizeof(path));
	while (args->exp[++i])
	{
		if (var_is_equal(args->exp[i], "PWD"))
		{
			str = ft_strjoin(str, path);
			free(args->exp[i]);
			args->exp[i] = ft_strdup(str);
			free(str);
			return ;
		}
	}
	args->exp[i] = ft_strjoin(str, path);
}

int	see_PWD_status(char **str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (var_is_equal(str[i], "PWD"))
			return(1);
		i++;
	}
	return (0);
}

void	do_cd(t_shell *args)
{
	int	error;

	error = 0;
	if(!see_PWD_status(args->exp))
		return ;
	if (!args->split[1] || args->split[1][0] == '~')
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
		g_status = 1;
		return ;
	}
	change_env_pwd(args);
	change_exp_pwd(args);
	g_status = 0;
}
