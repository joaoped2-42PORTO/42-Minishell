/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:38:33 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/13 18:38:46 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	helpft_word(char *str, int *l)
{
	while (str[*l] && str[*l] != ' ' && str[*l] != '\t' && !ft_checkspecial(str
			+ *l))
	{
		if (str[*l] == '\'' || str[*l] == '"')
			*l += ft_skipquotes(str + *l);
		(*l)++;
	}
}
