/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:22:48 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/15 11:37:44 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	checkstring(t_shell *args, t_tokens *tokens)
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
}

void	resetvalues(t_tokens *tokens)
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
	else
		checkstring(args, tokens);


}
