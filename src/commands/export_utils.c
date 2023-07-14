/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:05:06 by huolivei          #+#    #+#             */
/*   Updated: 2023/07/13 19:27:56 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	export_counting(t_shell *args, int *x, int *i)
{
	int	y;
	int	z;

	y = 0;
	z = 0;
	while (args->token->argm[++y])
	{
		if (suppforexportcounting(args, &y, &z) == 0)
			continue ;
		if (check_doubles_exp(args, y))
			args->exp[(*x)++] = ft_strdup(args->token->argm[y]);
		if (see_if_env(args->token->argm[y]) && check_doubles_env(args, y))
			args->env[(*i)++] = ft_strdup(args->token->argm[y]);
	}
	if (z == 0)
		g_status = 0;
}
