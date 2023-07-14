/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:23:47 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/14 18:16:43 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	checkforinput(t_shell *args, size_t *i)
{
	while (args->input[*i] && (args->input[*i] == ' '
			|| args->input[*i] == '\t'))
		(*i)++;
	if (*i == ft_strlen(args->input))
	{
		free(args->input);
		return (0);
	}
	return (1);
}

void	suppcountargs(char *str, int *i)
{
	while ((str[*i] && str[*i] == ' ') || (str[*i] && str[*i] == '\t'))
		(*i)++;
}

int	suppforquotes(char *str, int *i, int *dq, int *sq)
{
	if (str[*i] != '\'' && str[*i] != '"')
		return (0);
	if (str[*i] == '\'')
		*sq = 1;
	if (str[*i] == '"')
		*dq = 1;
	(*i)++;
	return (1);
}

void	suppforquotes2(char *str, int *i)
{
	while (str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		while (str[*i] && (str[*i] != '\'' || str[*i] != '"'))
			(*i)++;
	}
}

void	helpargs(char *str, int *i)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && !ft_checkspecial(str
			+ *i))
	{
		if (str[*i] == '\'' || str[*i] == '"')
			*i += ft_skipquotes(str + *i);
		if (*i >= (int)ft_strlen(str))
			return ;
		else
			(*i)++;
	}
}
