/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:05:06 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/15 14:06:45 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	see_env_size(t_shell *args)
{
	int	i;

	i = 0;
	while (args->env[i])
		i++;
	return (i);
}

char	**dup_env(char **str, char **str1)
{
	int	i;

	i = -1;
	while (str[++i])
		str1[i] = ft_strdup(str[i]);
	str1[i] = 0;
	return (str1);
}

void	free_matrix(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	see_split_size(t_shell *args)
{
	int	i;

	i = 0;
	while (args->split[i])
		i++;
	return (i);
}

void	exchange_memo(t_shell *args, char **env, char **exp, int *i, int *x)
{
	env = dup_env(args->env, env);
	exp = dup_env(args->exp, exp);
	free_matrix(args->env);
	free_matrix(args->exp);
	args->env = ft_calloc(*i + see_split_size(args), sizeof(char *));
	args->env = dup_env(env, args->env);
	args->exp = ft_calloc(*x + see_split_size(args), sizeof(char *));
	args->exp = dup_env(exp, args->exp);
}
