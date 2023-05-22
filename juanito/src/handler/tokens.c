/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:22:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/22 15:32:15 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*checkbars(t_shell *args, int *i)
{
	int		x;
	int		j;
	char	*src = NULL;

	x = *i;
	j = 0;
	src = ft_strdup(args->input);
	if (!src)
		free(src);
	while (args->input[x])
	{
		if (args->input[x] == '\\')
		{
			if (args->input[x + 1] == '\\')
			{
				printf("Error");
				return (0);
			}
			else if (args->input[x + 1] == '\'')
			{
				x++;
				src[j++] = args->input[x++];
			}
			else if (args->input[x + 1] == '"')
			{
				x++;
				src[j++] = args->input[x++];
			}
			x++;
		}
		else
			src[j++] = args->input[x++];
	}
	src[j] = '\0';
	return (src);
}

void	string(t_shell *args, int *i)
{
	int	j;
	int	x;

	j = 0;
	x = *i;
	while (args->input[x])
	{
		if (args->input[x] == '"' || args->input[x] == '\'')
			j++;
		x++;
	}
	if (j % 2 != 0)
		printf("Error");
	else
		checkbars(args, i);
}

int	stringnoquotes(t_shell *args, int *i)
{
	int	x;

	x = *i;
	checkbars(args, i);
	return (1);
}

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
	while(args->env[i])
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
	if (args->input[x] == '$')
	{
		if (args->input[x + 1] == '\'' || args->input[x + 1] == '"')
		{
			x++;
			string(args, &x);
		}
		else
			anotherfunction(args, i);
	}
}

int	checkisquote(t_shell *args, int *i)
{
	while (args->input[*i])
	{
		if (args->input[*i] == '"')
		{
			string(args, i);
			break ;
		}
		else if (args->input[*i] == '$')
		{
			treatingdollarsign(args, i);
			break ;
		}
		else
		{
			if (stringnoquotes(args, i) == 1)
				break ;
		}
	}
	return (1);
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
	if (checkisquote(args, &i) == 1)
		return (1);
	return (0);
}
