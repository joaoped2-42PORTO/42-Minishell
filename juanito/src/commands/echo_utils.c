/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 11:17:17 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/24 17:17:51 by joaoped2         ###   ########.fr       */
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

void	print_env_var(t_shell *args, char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->env[i], str, string_comp(args->env[i])))
		{
			while (args->env[i][j] != '=')
					j++;
			j++;
			while (args->env[i][j])
				printf("%c", args->env[i][j++]);
			return ;
		}
		i++;
	}
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

void	treatingdollarsign(t_shell *args, int *i)
{
	int	x;

	x = *i;
	while (args->input[x])
	{
		if (args->input[x] == '$')
		{
			if (args->input[x + 1] == '\'' || args->input[x + 1] == '"')
			{
				x++;
				string(args, &x);
				break ;
			}
			else
			{
				anotherfunction(args, &x);
				break ;
			}
		}
		x++;
	}
}

int	isdollar(t_shell *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args->input[i])
	{
		if (args->input[i] == '$')
		{
			j++;
			while (args->input[i] != ' ')
				i++;
			return (i);
			break ;
		}
		i++;
	}
	return (j);
}

int	checkafterdollar(t_shell *args)
{
	int	i;

	i = 0;
	while (args->input[i])
	{
		if (args->input[i] == '$')
		{
			while (args->input[i] != ' ')
				i++;
			break ;
		}
		i++;
	}
	return (i);
}

void	getindexafterdollar(t_shell *args, int *i)
{
	int	x;

	x = *i;
	if (args->input[x] != '\0')
		string(args, &x);
}
