/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:08:32 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/29 14:21:46 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
