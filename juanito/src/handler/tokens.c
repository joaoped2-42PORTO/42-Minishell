/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:22:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/25 15:48:08 by joaoped2         ###   ########.fr       */
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

	x = *i;
	j = 0;
	k = 0;
	src = (char *)malloc((ft_strlen(args->input) + 1) * sizeof(char));
	str = (char *)malloc((ft_strlen(*args->env) + 1) * sizeof(char));
	if (!src)
		free(src);
	while (args->input[x])
	{
		if (args->input[x] != '"')
		{
			if (args->input[x] == '$')
			{
				x++;
				str = print_env_var(args, &args->input[x]);
				while (str[k])
					src[j++] = str[k++];
			}
			else
				src[j++] = args->input[x];
		}
		x++;
	}
	src[j] = '\0';
	return (src);
}

int	string(t_shell *args, int *i)
{
	int	j;
	int	x;

	j = 0;
	x = *i;
	while (args->input[x])
	{
		if (args->input[x] == '"')
			j++;
		x++;
	}
	x = *i;
	if (j % 2 != 0)
	{
		printf("Error");
		return (0);
	}
	return (1);
}

void	checkisquote(t_shell *args, int *i)
{
	int	x;

	x = *i;
	while (args->input[x])
	{
		if (args->input[x] == '"')
		{
			string(args, &x);
			break ;
		}
		else
		{
			checkbars(args, &x);
			break ;
		}
		x++;
	}
}

int	countvalues(t_shell *args)
{
	int	i;

	i = 0;
	while (args->input[i] == ' ')
		i++;
	while (args->input[i] != ' ')
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
