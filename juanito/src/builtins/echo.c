/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:34:54 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/27 14:42:08 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_echo(t_shell *args)
{
	int	i;

	if (!ft_strncmp(args->split[1], "-n", 2))
	{
		i = 8;
		while (args->input[i])
			write(1, &args->input[i++], 1);
	}
	else
	{
		i = 5;
		while (args->input[i])
			write(1, &args->input[i++], 1);
		write(1, "\n", 1);
	}
}
