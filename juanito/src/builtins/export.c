/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:14:04 by neddy             #+#    #+#             */
/*   Updated: 2023/04/27 12:32:22 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_export(t_shell *args)
{
	int	i;
	int	j;
	int	x;

	x = 0;
	j = 7;
	i = 0;
	while (args->env[i])
		i++;
	args->env[i] = malloc(sizeof(char) * ft_strlen(args->input));
	while(args->input[j])
		args->env[i][x++] = args->input[j++];
	args->env[i][x] = '\0';
	i++;
	args->env[i] = 0;
}
