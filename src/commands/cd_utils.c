/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:53:47 by huolivei          #+#    #+#             */
/*   Updated: 2023/07/20 23:31:38 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	change_pwd(char **str1, t_shell *args)
{
	int		i;
	char	*str;

	str = "OLDPWD=";
	i = -1;
	while (str1[++i])
	{
		if (var_is_equal(str1[i], "OLDPWD"))
		{
			str = ft_strjoin(str, &args->path[4]);
			free(str1[i]);
			str1[i] = ft_strdup(str);
			free(str);
			return (1);
		}
	}
	return (0);
}

void	first_old_pwd_exp(t_shell *args)
{
	int		i;
	char	**exp;
	char	*str;

	str = "OLDPWD=";
	i = see_exp_size(args);
	exp = ft_calloc(i + 2, sizeof(char *));
	exchange_memo_exp(args, exp, &i);
	str = ft_strjoin(str, &args->path[4]);
	args->exp[i++] = ft_strdup(str);
	args->exp[i] = 0;
	free (str);
	free_matrix(exp);
}

void	first_old_pwd_env(t_shell *args)
{
	int		i;
	char	**exp;
	char	*str;

	str = "OLDPWD=";
	i = see_env_size(args);
	exp = ft_calloc(i + 2, sizeof(char *));
	exchange_memo_env(args, exp, &i);
	str = ft_strjoin(str, &args->path[4]);
	args->env[i++] = ft_strdup(str);
	args->env[i] = 0;
	free (str);
	free_matrix(exp);
}

void	change_env_oldpwd(t_shell *args)
{
	if (change_pwd(args->env, args) && change_pwd(args->exp, args))
		return ;
	first_old_pwd_env(args);
	first_old_pwd_exp(args);
}

void	terminate_cd_sucess(t_shell *args)
{
	change_env_pwd(args);
	change_exp_pwd(args);
	change_env_oldpwd(args);
	g_status = 0;
}
