/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:22:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/17 15:42:05 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	checkisnum(t_shell *args, int *i)
{
	while (args->input[i])
	{
		if (args->input[i] >= 0 && args->input[i] <= 9)
			write(1, &args->input[i++], 1);
		else
			break ;
	}
}

void	string(t_shell *args, int *i)
{
	int	j;
	int	*x;

	j = 1;
	x = &i;
	while (args->input[*i])
	{
		if (args->input[*i] == '"')
			j++;
		else
			*i++;
	}
	if (j % 2 != 0)
		printf("Error\n");
	else
	{
		while (args->input[x])
		{
			if (args->input[x] >= 'a' && args->input[x] <= 'z')
				write(1, &args->input[x], 1);
			else if (args->input[x] >= 'A' && args->input[x] <= 'Z')
				write(1, &args->input[x], 1);
			else if (checkisnum(args, x))
				continue ;
			else
				x++;
		}
	}
}

int	stringnoquotes(t_shell *args, int *i)
{
	while (args->input[*i])
	{
		if (args->input[*i] >= 'a' && args->input[*i] <= 'z')
			write(1, &args->input[*i++], 1);
		else if (args->input[*i] >= 'A' && args->input[*i] <= 'Z')
			write(1, &args->input[*i++], 1);
		else if (checkisnum(args, &i) == 1)
			*i++;
		else if (args->input[*i] == '"')
			string(args, &i);
		else
			*i++;
	}
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

int	checkisquote(t_shell *args)
{
	int	i;

	i = 0;
	while (args->input[i])
	{
		if (args->input[i] == '\'' || args->input[i] == '"')
		{
			if (args->input[i] == '"')
			{
				i++;
				string(args, &i);
			}
		}
		else if (args->input[i] == '`' || args->input[i] == '\\')
		{
			if (args->input[i] == '\\')
			{
				i++;
				write(1, &args->input[i], 1);
			}
		}
		else
			stringnoquotes(args, &i);
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

void	resetvalues(t_shell *args, t_tokens *tokens)
{
	int	i;

	i = 0;
	while (args->input[i])
	{
		if (args->input[i] == '"')
			tokens->doublequote = 0;
		else if (args->input[i] == '\'')
			tokens->singlequote = 0;
		else if (args->input[i] == '\\')
			tokens->backslash = 0;
		else if (args->input[i] == ';')
			tokens->semicolon = 0;
		else if (args->input[i] == '<')
			tokens->redinput = 0;
		else if (args->input[i] == '>')
			tokens->redioutput = 0;
		else if (args->input[i] == '|')
			tokens->pipe = 0;
		else if (args->input[i] == '$')
			tokens->dollar = 0;
		i++;
	}

}

void	countvalues(t_shell *args, t_tokens *tokens)
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
		while (args->input[i] != ' ')
			i++;
	checkisquote(args);
}
