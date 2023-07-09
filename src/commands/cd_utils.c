/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:53:47 by huolivei          #+#    #+#             */
/*   Updated: 2023/07/08 22:35:59 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	change_pwd(char **str1)
{
	int		i;
	char	path[1000];
	char	*str;

	str = "OLDPWD=";
	i = -1;
	getcwd(path, sizeof(path));
	while (str1[++i])
	{
		if (var_is_equal(str1[i], "OLDPWD"))
		{
			str = ft_strjoin(str, path);
			free(str1[i]);
			str1[i] = ft_strdup(str);
			free(str);
			return (1);
		}
	}
	return (0);
}

void	first_old_pwd(char **str1)
{
	int		i;
	char	path[1000];
	char	*str;

	str = "OLDPWD=";
	i = -1;
	getcwd(path, sizeof(path));
	while (str1[++i])
	{
		if (var_is_equal(str1[i], "PWD"))
		{
			str = ft_strjoin(str, path);
			free(str1[i]);
			str1[i] = ft_strdup(str);
			free(str);
			break ;
		}
	}
}

void	change_env_oldpwd(t_shell *args)
{
	if (change_pwd(args->env) && change_pwd(args->exp))
		return ;
	first_old_pwd(args->env);
	first_old_pwd(args->exp);
}