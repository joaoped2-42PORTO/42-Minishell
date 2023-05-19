/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:22:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/19 14:58:43 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	string(t_shell *args, int *i)
{
	int	j;
	int	x;

	j = 1;
	x = *i;
	while (args->input[*i])
	{
		if (args->input[*i] == '"')
			j++;
		else
			i++;
	}
	if (j % 2 != 0)
		printf("Error\n");
	else
	{
		while (args->input[x])
		{
			if (args->input[x] >= 32 && args->input[x] <= 126)
				write(1, &args->input[x], 1);
			x++;
		}
	}
}

int	stringnoquotes(t_shell *args, int *i)
{
	int	x;

	x = *i;
	while (args->input[x])
		write(1, &args->input[x++], 1);
	return (1);
}

int	punctuation(t_shell *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args->input[i])
	{
		if (args->input[i] == ';' || args->input[i] == '(')
			j++;
		else if (args->input[i] == ')' || args->input[i] == '{')
			j++;
		else if (args->input[i] == '}' || args->input[i] == '[')
			j++;
		else if (args->input[i] == ']' || args->input[i] == ',')
			j++;
		else if (args->input[i] == '.' || args->input[i] == ':')
			j++;
		i++;
	}
	return (j);
}

int	checkisquote(t_shell *args, int *i)
{
	while (args->input[*i])
	{
		if (args->input[*i] == '"')
			string(args, i);
		else if (args->input[*i] == '\\')
		{
			i++;
			write(1, &args->input[*i], 1);
		}
		else
		{
			if (stringnoquotes(args, i) == 1)
				break ;
		}
		i++;
	}
	return (1);
}

int	operators(t_shell *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args->input[i])
	{
		if (args->input[i] == '+' || args->input[i] == '-')
			j++;
		else if (args->input[i] == '*' || args->input[i] == '/')
			j++;
		else if (args->input[i] == '%' || args->input[i] == '=')
			j++;
		else if (args->input[i] == '!' || args->input[i] == '>')
			j++;
		else if (args->input[i] == '<' || args->input[i] == '&')
			j++;
		else if (args->input[i] == '|')
			j++;
		i++;
	}
	return (j);
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
