/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:02:23 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/09 01:24:18 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_rd2(t_shell *args, t_comand *ag, int *i, int *x)
{
	if (args->split[*i][0] == '>')
	{
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->flag = 1;
	}
	else if (args->split[*i][0] == '<')
	{
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		if (args->split[*i][0] == '>')
			(*i)++;
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->flag = 1;
	}
}

void	check_rd(t_shell *args, t_comand *ag, int *i, int *x)
{
	if (args->split[*i][0] == '>' && args->split[*i][1] == '>')
	{
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->flag = 1;
	}
	else if (args->split[*i][0] == '<' && args->split[*i][1] == '<')
	{
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->flag = 1;
	}
	else
		check_rd2(args, ag, i, x);
}
