/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:46:04 by huolivei          #+#    #+#             */
/*   Updated: 2023/05/20 17:19:52 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	string_comp(char *str1)
{
	int	j;

	j = 0;
	while (str1[j])
	{
		j++;
		if (str1[j] == '=')
			break ;
	}
	return (j);
}

void	exchange_memo_unset(t_shell *args, char **str, int *i)
{
	str = dup_env(args->env, str);
	free_matrix(args->env);
	args->env = ft_calloc(*i, sizeof(char *));
}

void	unset(t_shell *args)
{
	char	**str;
	int		i;
	int		j;
	int		x;
	int		size;

	x = 0;
	j = 0;
	i = 0;
	size = see_env_size(args);
	str = ft_calloc((size + 1), sizeof(char *));
	exchange_memo_unset(args, str, &size);
	while (args->split[i++])
	{
		if (args->split[i] == 0)
			break ;
		j = 0;
		while (str[j])
		{
			if (ft_strncmp(args->split[i], str[j], string_comp(str[j])))
			{
				args->env[x++] = ft_strdup(str[j]);
			}
			if (args->split[i + 1] == 0)
				free(str[j]);
			j++;
		}
	}
	free(str);
	args->env[x] = 0;
}
