/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:17:36 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/22 14:24:33 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cleandel(t_shell *args)
{
	if (args->input == NULL)
	{
		free(args->input);
		free(args->new_env);
		free(args);
		printf("\n");
		return (0);
	}
	else
		return (1);
}

void	freesformain(t_shell *args)
{
	free(args->input);
	free(args->exp);
}
