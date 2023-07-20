/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:47:52 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/20 14:31:43 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	suppforexportcounting(t_shell *args, int *y, int *z)
{
	if (!see_chars(args->token->argm[*y]))
	{
		ft_putendl_fd("Char not supported", 2);
		g_status = 1;
		*z = 1;
		if (args->token->argm[(*y) + 1])
			(*y)++;
		else
			return (0);
	}
	return (1);
}

int	ft_isalnum2(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| c == '_')
		return (1);
	return (0);
}

int	see_chars(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) || str[0] == '=' || !str[0])
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum2(str[i]))
			return (0);
		i++;
	}
	return (1);
}
