/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:05:06 by huolivei          #+#    #+#             */
/*   Updated: 2023/07/03 22:46:39 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	exchange_memo_env(t_shell *args, char **env, int *i)
{
	env = dup_env(args->env, env);
	free_matrix(args->env);
	args->env = ft_calloc(*i + see_split_size(args), sizeof(char *));
	args->env = dup_env(env, args->env);
}

void	exchange_memo_exp(t_shell *args, char **exp, int *x)
{
	exp = dup_env(args->exp, exp);
	free_matrix(args->exp);
	args->exp = ft_calloc(*x + see_split_size(args), sizeof(char *));
	args->exp = dup_env(exp, args->exp);
}

int	see_chars(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	export_counting(t_shell *args, int *x, int *i)
{
	int	y;

	y = 0;
	while (args->split[++y])
	{
		if (!see_chars(args->split[y]))
		{
			printf("Char not supported\n");
			if (args->split[y + 1])
				y++;
			else
				break;
		}
		if (!check_doubles_env(args, y) && !check_doubles_exp(args, y))
			continue ;
		else if (!see_if_env(args->split[y]))
			args->exp[(*x)++] = ft_strdup(args->split[y]);
		else
		{
			args->env[(*i)++] = ft_strdup(args->split[y]);
			args->exp[(*x)++] = ft_strdup(args->split[y]);
		}
	}
}
