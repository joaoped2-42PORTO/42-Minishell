/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:46:04 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/17 15:12:46 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exchange_memo_unset_exp(t_shell *args, char **str, int *i)
{
	str = dup_env(args->exp, str);
	free_matrix(args->exp);
	args->exp = ft_calloc(*i + 1, sizeof(char *));
}

void	exchange_memo_unset(t_shell *args, char **str, int *i)
{
	str = dup_env(args->env, str);
	free_matrix(args->env);
	args->env = ft_calloc(*i + 1, sizeof(char *));
}

void	change_env_unset(t_shell *args, char **env, char *str1, int *y)
{
	int	j;

	j = 0;
	while (env[j])
	{
		if (ft_strncmp(str1, env[j], variable_size(env[j])))
		{
			args->env[(*y)++] = ft_strdup(env[j]);
		}
		free(env[j]);
		j++;
	}
}

void	change_exp_unset(t_shell *args, char **exp, char *str1, int *x)
{
	int	j;

	j = 0;
	while (exp[j])
	{
	if (ft_strncmp(str1, exp[j], variable_size(exp[j])))
	{
			args->exp[(*x)++] = ft_strdup(exp[j]);
	}
	free(exp[j]);
	j++;
	}
}
void	loop_unset(t_shell *args, char **exp, char **env, char *str1)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	change_env_unset(args, env, str1, &y);
	change_exp_unset(args, exp, str1, &x);
	args->env[y] = 0;
	args->exp[x] = 0;
}

void	unset(t_shell *args, char *str1)
{
	char	**str;
	char	**exp;
	int		size;
	int		size_exp;

	size = see_env_size(args);
	size_exp = see_exp_size(args);
	str = ft_calloc((size + 1), sizeof(char *));
	exp = ft_calloc((size_exp + 1), sizeof (char *));
	exchange_memo_unset(args, str, &size);
	exchange_memo_unset_exp(args, exp, &size_exp);
	loop_unset(args, exp, str, str1);
	free(exp);
	free(str);

}

void	do_unset(t_shell *args)
{
	char	*str;
	int		i;

	i = 0;
	while(args->split[++i])
	{
		if (args->split[i] == 0)
			break ;
		str = ft_strdup(args->split[i]);
		unset(args, str);
		free(str);
	}
}
