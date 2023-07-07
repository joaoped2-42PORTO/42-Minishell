/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:47:52 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/07 14:48:05 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	suppforexportcounting(t_shell *args, int *y, int *z)
{
	if (!see_chars(args->token->argm[*y]))
	{
		printf("Char not supported\n");
		g_status = 1;
		*z = 1;
		if (args->token->argm[(*y) + 1])
			(*y)++;
		else
			return (0);
	}
	return (1);
}
