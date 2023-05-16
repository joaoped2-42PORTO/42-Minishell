/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:22:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/16 15:34:28 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checkisnum(t_shell *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args->input[i])
	{
		if (args->input[i] >= 0 && args->input[i] <= 9)
			j++;
		i++;
	}
	return (j);
}

int	checkisletter(t_shell *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args->input[i])
	{
		if (args->input[i] >= 'a' && args->input[i] <= 'z')
			j++;
		else if (args->input[i] >= 'A' && args->input[i] <= 'Z')
			j++;
		i++;
	}
	return (j);
}

int	checkissymbol(t_shell *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args->input[i])
	{
		if (args->input[i] == '.' || args->input[i] == ',')
			j++;
		else if (args->input[i] == ';' || args->input[i] == ':')
			j++;
		i++;
	}
	return (j);
}

int	checkisquote(t_shell *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args->input[i])
	{
		if (args->input[i] == '\'' || args->input[i] == '"')
			j++;
		else if (args->input[i] == '`')
			j++;
		i++;
	}
	return (j);
}

int	checkissignals(t_shell *args)
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
		else if (args->input[i] == '%' || args->input[i] == '#')
			j++;
		i++;
	}
	return (j);
}

int	checkotherchars(t_shell *args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args->input[i])
	{
		if (args->input[i] == '$' || args->input[i] == '\\')
			j++;
		else if (args->input[i] == '{' || args->input[i] == '}')
			j++;
		else if (args->input[i] == '(' || args->input[i] == ')')
			j++;
		i++;
	}
	return (j);
}

void	callchecker(t_shell *args)
{
	checkisnum(args);
	checkisletter(args);
	checkissymbol(args);
	checkisquote(args);
	checkissignals(args);
	checkotherchars(args);
}

/*void	checkstring(t_shell *args)
{
	int	i;
	int	checkp;

	i = 0;
	while (args->input[i])
	{
		if (args->input[i] == "\"")
		{
			checkp = i;
			while (args->input[i])
				i++;
			i--;
			if (args->input[i] == "\"")
				i = checkp;
			else
			{
				printf("Error!");
				break ;
			}
		}
	}
}*/

//Preciso de fazer verificacoes dentro de verificacoes durante a leitura da string para dividir os diferentes tokens


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
	checkstring(args);
}
