/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:53:47 by huolivei          #+#    #+#             */
/*   Updated: 2023/05/11 12:54:39 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	change_pwd(char **str1)
{
	int	i;
	char	path[1000];
	char	*str;

	str = "OLDPWD=";
	i = -1;
	getcwd(path, sizeof(path));
	while (str1[++i])
	{
		if (!ft_strcmp(str1[i], "OLDPWD"))
		{
			str = ft_strjoin(str, path);
			str1[i] = ft_strdup(str);
			free(str);
			return (1);
		}
	}
	return (0);
}

void	first_old_pwd(char **str1)
{
	int	i;
	char	path[1000];
	char	*str;

	str = "OLDPWD=";
	i = -1;
	getcwd(path, sizeof(path));
	while (str1[++i])
	{
		if (!ft_strcmp(str1[i], "PWD"))
		{
			str = ft_strjoin(str, path);
			str1[i] = ft_strdup(str);
			free(str);
			break;
		}
	}
}

void	change_env_oldpwd(t_shell *args)
{
	int flag;

	flag = 0;
	if (args->new_env[0] == 0)
	{
		if(change_pwd(args->env))
			flag = 1;
	}
	else
	{
		if(change_pwd(args->new_env))
			flag = 1;
	}
	if (flag == 0)
		first_old_pwd(args->env);
	return ;
}
