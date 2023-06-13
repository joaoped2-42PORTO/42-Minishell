/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:17:17 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/13 14:22:32 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	string_comp(char *str1)
{
	int	j;

	j = 0;
	while (str1[j])
	{
		j++;
		if (str1[j] == '=')
			break ;
	}
	return (j);
}
/*
char	*print_env_var(t_shell *args, char *str)
{
	int		i;
	int		j;
	char	*src;

	i = 0;
	j = 0;
	src = NULL;
	while (args->env[i])
	{
		j = 0;
		while (args->env[i][j] && str[j] && args->env[i][j] == str[j])
			j++;
		if (args->env[i][j] == '=' && str[j] == '\0')
		{
			j++;
			free(src);
			src = ft_strdup(&args->env[i][j]);
			break ;
		}
		i++;
	}
	if (src == NULL)
		return (NULL);
	return (src);
}*/

void	put_var(t_shell *args, char	*str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (args->input[i] != '$')
		i++;
	i++;
	while (args->input[i])
		str[j++] = args->input[i++];
}

void	anotherfunction(t_shell *args, int *i)
{
	char	*src;

	src = ft_calloc(ft_strlen(args->input), sizeof(char));
	while (args->input[*i])
	{
		if (args->input[*i] == '$')
		{
			put_var(args, src);
			print_env_var(args, src);
			return ;
		}
		i++;
	}
}
