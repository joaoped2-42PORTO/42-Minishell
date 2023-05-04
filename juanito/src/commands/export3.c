/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:57:16 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/04 12:57:29 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(t_shell *args)
{
	int	i;

	i = 0;
	if (args->new_env[0] == 0)
	{
		while (args->env[i])
			printf("declare -x %s\n", args->env[i++]);
	}
	else
	{
		while (args->new_env[i])
			printf("declare -x %s\n", args->new_env[i++]);
	}
}
