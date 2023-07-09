/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:08:32 by huolivei          #+#    #+#             */
/*   Updated: 2023/07/09 01:12:37 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	variable_size(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
		if (str[i] == '=')
			break ;
	}
	return (i);
}

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

int	check_chars_unset(char *str1)
{
	int	i;

	i = 0;
	if (ft_isdigit(str1[0]))
	{
		printf("Char not supported\n");
		return (0);
	}
	while (str1[i])
	{
		if (!ft_isalnum2(str1[i++]))
		{
			printf("Char not supported\n");
			return (0);
		}
	}
	return (1);
}
