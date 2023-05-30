/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:44:35 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/29 17:46:02 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanstring(t_shell *args, int i)
{
	char	*str;
	char	*dollar;
	int		j;

	j = 0;
	str = checkbars(args, &i);
	if (!str)
	{
		free(str);
		return ;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0')
		{
			dollar = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
			i++;
			while (str[i] != ' ' && str[i] != '\0' && str[i] != '$')
				dollar[j++] = str[i++];
			i--;
			printf("%s", print_env_var(args, dollar));
			if (str[i] == ' ')
				printf("%c", str[i]);
			j = 0;
			free(dollar);
		}
		else	
			printf("%c", str[i]);
		i++;
	}
}

int	checkforspacesinstring(t_shell *args, int i)
{
	int	j;

	j = 0;
	while (args->input[i])
	{
		while (args->input[i] != ' ')
			i++;
		while (args->input[i] == ' ')
		{
			j++;
			i++;
		}
		return (j);
		i++;
	}
	return (j);
}

void	checksplitcontent(t_shell *args)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 1;
	x = countvalues(args);
	if (args->split[j][i] == '-' && args->split[j][i + 1] == 'n')
	{
		while (args->split[j][i] == '-')
		{
			if (args->split[j][i] == '-' && args->split[j][i + 1] == 'n')
			{
				i++;
				while (args->split[j][i] == 'n')
					i++;
				if (args->split[j][i] == '\0')
				{
					j++;
					x += i;
					x += checkforspacesinstring(args, x);
					i = 0;
				}
				else
				{
					cleanstring(args, x);
					return ;
				}
			}
			else
			{
				cleanstring(args, x);
				return ;
			}
		}
	}
	else
	{
		i = countvalues(args);
		cleanstring(args, i);
		printf("\n");
		return ;
	}
	cleanstring(args, x);
}

void	do_echo(t_shell *args)
{
	checksplitcontent(args);
}
