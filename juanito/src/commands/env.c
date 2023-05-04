/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:27:31 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/04 12:19:58 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_shell *args)
{
	int	i;

	i = 0;
	if (args->new_env[0] == 0)
	{
		while (args->env[i])
			printf("%s\n", args->env[i++]);
	}
	else
	{
		while (args->new_env[i])
			printf("%s\n", args->new_env[i++]);
	}
}

int	see_env_size(t_shell *args)
{
	int	i;

	i = 0;
	if (args->new_env[0] == 0)
	{
		while (args->env[i])
			i++;
		args->env[i] = malloc(sizeof(char) * ft_strlen(args->input));
	}
	else
	{
		while (args->new_env[i])
			i++;
		args->new_env[i] = malloc(sizeof(char) * ft_strlen(args->input));
	}
	return (i);
}
