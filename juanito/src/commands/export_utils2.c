/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:18:42 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/29 14:21:16 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_doubles_exp(t_shell *args, int y)
{
	int	j;

	j = 0;
	while (args->exp[j])
	{
		if (!ft_strncmp(args->split[y], args->exp[j],
				variable_size(args->exp[j])))
		{
			free(args->exp[j]);
			args->exp[j] = ft_strdup(args->split[y]);
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
	while (see_if_env(args->split[y]) && args->env[j])
	{
		if (!ft_strncmp(args->split[y], args->env[j],
				variable_size(args->env[j])))
		{
			free(args->env[j]);
			args->env[j] = ft_strdup(args->split[y]);
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
