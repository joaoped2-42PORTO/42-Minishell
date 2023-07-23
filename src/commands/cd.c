/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:27:59 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/23 15:20:49 by huolivei         ###   ########.fr       */
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
			free(args->pwd);
			str = ft_strjoin(str, path);
			free(args->env[i]);
			args->env[i] = ft_strdup(str);
			args->pwd = ft_strdup(str);
			free(str);
			return ;
		}
	}
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
}

int	see_pwd_status(char **str, t_shell *args)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (var_is_equal(str[i], "PWD"))
		{
			free (args->path);
			args->path = ft_strdup(str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	do_cd(t_shell *args)
{
	int	error;

	error = 0;
	if (!see_pwd_status(args->exp, args))
		return ;
	if (!args->split[1] || args->token->argm[1][0] == '~')
	{
		change_env_oldpwd(args);
		ft_homedk(args);
		change_env_pwd(args);
		change_exp_pwd(args);
		return ;
	}
	error = chdir(args->token->argm[1]);
	if (error != 0)
	{
		perror("Error");
		change_env_pwd(args);
		change_exp_pwd(args);
		g_status = 1;
		return ;
	}
	terminate_cd_sucess(args);
}
