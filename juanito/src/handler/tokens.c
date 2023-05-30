/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:22:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/29 17:30:13 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*checkbars(t_shell *args, int *i)
{
	int		x;
	int		j;
	char	*src = NULL;
	int		p;

	x = *i;
	j = 0;
	p = 0;
	free(src);
	src = (char *)malloc((ft_strlen(args->input) + 1) * sizeof(char));
	if (!src)
		free(src);
	while (args->input[x])
	{
		if (valid_input(args) == 0)
		{
			printf("Error");
			break ;
		}
		if (args->input[x] == '"')
		{
			p++;
			x++;
		}
		else if (p % 2 != 0)
			src[j++] = args->input[x++];
		else
		{
			if (args->input[x] == '\'')
				x++;
			while (args->input[x] == ' ' && args->input[x + 1] == ' ')
				x++;
			src[j++] = args->input[x++];
		}
	}
	src[j] = '\0';
	return (src);
}

int	countvalues(t_shell *args)
{
	int	i;

	i = 0;
	while (args->input[i] == ' ')
		i++;
	while (args->input[i] != ' ' && args->input[i])
		i++;
	while (args->input[i] == ' ')
		i++;
	return (i);
}
