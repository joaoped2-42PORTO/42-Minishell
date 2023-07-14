/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:18:42 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/13 19:20:40 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	var_is_equal(char *str, char *str1)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	while (str1[j] && str1[j] != '=')
		j++;
	if (!ft_strncmp(str, str1, variable_size(str)) && i == j)
		return (1);
	return (0);
}

int	check_doubles_exp(t_shell *args, int y)
{
	int	j;

	j = 0;
	while (args->exp[j])
	{
		if (var_is_equal(args->token->argm[y], args->exp[j]))
		{
			if (see_if_env(args->token->argm[y]))
			{
				free(args->exp[j]);
				args->exp[j] = ft_strdup(args->token->argm[y]);
				return (0);
			}
			else
				return (0);
		}
		j++;
	}
	return (1);
}

int	check_doubles_env(t_shell *args, int y)
{
	int	j;

	j = 0;
	while (see_if_env(args->token->argm[y]) && args->env[j])
	{
		if (var_is_equal(args->token->argm[y], args->env[j]))
		{
			free(args->env[j]);
			args->env[j] = ft_strdup(args->token->argm[y]);
			return (0);
		}
		j++;
	}
	return (1);
}

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
