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

int	checksplitcontent(t_shell *args)
{
	int	i;

	i = 0;
	while (args->split[1][i])
		i++;
	return (i);
}

void	cleanstring(t_shell *args)
{
	char	*str;
	char	*dollar;
	int		i;
	int		j;

	i = countvalues(args);
	j = 0;
	str = checkbars(args, &i);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			dollar = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
			i++;
			while (str[i] != ' ' && str[i] != '\0')
				dollar[j++] = str[i++];
			printf("%s", print_env_var(args, dollar));
			free(dollar);
			j = 0;
		}
		printf("%c", str[i]);
		i++;
	}
}

void	do_echo(t_shell *args)
{
	checksplitcontent(args);
	if (!args->split[1])
		printf("\n");
	else if (checksplitcontent(args) == 2)
		cleanstring(args);
	else
	{
		cleanstring(args);
		printf("\n");
	}
}
