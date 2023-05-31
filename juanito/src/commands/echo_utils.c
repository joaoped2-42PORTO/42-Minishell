/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:17:17 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/31 16:19:09 by joaoped2         ###   ########.fr       */
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

char	*print_env_var(t_shell *args, char *str)
{
	int	i;
	int	j;
	int	k;
	char	*src = NULL;

	j = 0;
	i = 0;
	k = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->env[i], str, string_comp(args->env[i])))
		{
			while (args->env[i][j] != '=')
				j++;
			j++;
			free(src);
			src = ft_calloc(ft_strlen(&args->env[i][j]) + 1, sizeof(char));
			while (args->env[i][j])
				src[k++] = args->env[i][j++];
			src[k] = '\0';
		}
		i++;
	}
	if (k == 0)
	{
		printf("");
		return (0);
	}
	return (src);
}

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
