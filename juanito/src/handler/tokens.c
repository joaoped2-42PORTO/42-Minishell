/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:22:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/29 15:35:54 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*checkbars(t_shell *args, int *i)
{
	int		x;
	int		j;
	int		k;
	char	*src;
	char	*str;
	int		p;

	x = *i;
	j = 0;
	k = 0;
	p = 0;
	src = (char *)malloc((ft_strlen(*args->env) + 1) * sizeof(char));
	if (!src)
		free(src);
	while (args->input[x])
	{
		k = 0;
		if (args->input[x] == '$' && args->input[x + 1] != ' ')
		{
			str = (char *)malloc((ft_strlen(*args->env) + 1) * sizeof(char));
			x++;
			str = print_env_var(args, &args->input[x]);
			while (args->input[x] != '\0' && args->input[x] != ' ')
				x++;
			while (str[k])
				src[j++] = str[k++];
			free(str);
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
	if (args->input[i] == '-')
	{
		while (args->input[i] != ' ')
			i++;
		i++;
	}
	while (args->input[i] == ' ')
		i++;
	return (i);
}
