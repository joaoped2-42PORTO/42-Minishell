/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:47:52 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/08 17:28:48 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	see_chars(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}
