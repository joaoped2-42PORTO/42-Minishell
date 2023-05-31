/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:22:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/31 17:06:28 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*checkbars(t_shell *args, int *i)
{
	int		x;
	int		j;
	char	*str = NULL;
	char	*ptr = NULL;
	char	*ptr2 = NULL;
	int		p;
	int		k;

	x = *i;
	j = 0;
	p = 0;
	k = 0;
	str = (char *)malloc((ft_strlen(args->input) + 1) * sizeof(char));
	ptr = (char *)malloc((ft_strlen(*args->env) + 1) * sizeof(char));
	ptr2 = (char *)malloc((ft_strlen(*args->env) + 1) * sizeof(char));
	if (!ptr || !str || !ptr2)
	{
		free(ptr);
		free(str);
		free(ptr2);
		return NULL;
	}
	while (args->input[x])
	{
		if (valid_input(args) == 0)
		{
			printf("Error");
			break ;
		}
		if (args->input[x] == '"' || p % 2 != 0)
		{
			if (args->input[x] == '"')
				x++;
			else if (args->input[x] == '$' && args->input[x + 1] != ' ' && args->input[x + 1] != '\0')
			{
				x++;
				while (args->input[x] != ' ' && args->input[x] != '\0' && args->input[x] != '$' && args->input[x] != '"')
					str[k++] = args->input[x++];
				x++;
				p++;
				str[k] = '\0';
				free(ptr2);
				ptr2 = print_env_var(args, str);
				k = 0;
				while (ptr2[k])
					ptr[j++] = ptr2[k++];
				free(ptr2);
			}
			else
				ptr[j++] = args->input[x++];
			p++;
		}
		else if (p % 2 == 0)
		{
			if (args->input[x] == '$' && args->input[x + 1] != ' ' && args->input[x + 1] != '\0' && args->input[x + 1] != '$')
			{
				x++;
				while (args->input[x] != ' ' && args->input[x] != '\0' && args->input[x] != '$' && args->input[x] != '"')
					str[k++] = args->input[x++];
				str[k] = '\0';
				free(ptr2);
				ptr2 = print_env_var(args, str);
				k = 0;
				while (ptr2[k])
					ptr[j++] = ptr2[k++];
				free(ptr2);
				free(str);
			}
			else
			{
				while (args->input[x] == ' ' && args->input[x + 1] == ' ')
					x++;
				ptr[j++] = args->input[x++];
			}
		}
		else
		{
			if (args->input[x] == '\'')
				x++;
			while (args->input[x] == ' ' && args->input[x + 1] == ' ')
				x++;
			ptr[j++] = args->input[x++];
		}
	}
	ptr[j] = '\0';
	free(str);
	free(ptr2);
	return (ptr);
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
