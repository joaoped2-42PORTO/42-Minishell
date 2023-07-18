/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:02:23 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/18 11:43:03 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_rd2(t_shell *args, t_comand *ag, int *i, int *x)
{
	if (args->split[*i][0] == '>' && !args->split[*i][1])
	{
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->flag = 1;
	}
	else if (args->split[*i][0] == '<' && !args->split[*i][1])
	{
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		if (*i < see_split_size(args))
		{
			if (args->split[*i][0] == '>')
				(*i)++;
		}
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->flag = 1;
	}
}

void	check_rd(t_shell *args, t_comand *ag, int *i, int *x)
{
	if (args->split[*i][0] == '>' && args->split[*i][1] == '>'
		&& !args->split[*i][2])
	{
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->flag = 1;
	}
	else if (args->split[*i][0] == '<' && args->split[*i][1] == '<'
		&& !args->split[*i][2])
	{
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->flag = 1;
	}
	else
		check_rd2(args, ag, i, x);
}

void	loop_helper(t_comand *ag, t_shell *args, int *i, int *j)
{
	if (args->split[*i] && !checkpipered(args, i)
		&& check_for_first_redir(args->split, i)
		&& ft_strlen(args->split[*i]) > 0)
		ag->argm[(*j)++] = ft_strdup(args->split[(*i)++]);
	else if (args->split[*i] && !checkpipered(args, i)
		&& check_for_first_redir(args->split, i))
		(*i)++;
}

void	init_helper(t_comand *ag, t_shell *args)
{
	ag->flag = 0;
	ag->argm = ft_calloc(see_split_size(args) + 1, sizeof(char *));
	ag->redir = ft_calloc(see_split_size(args) + 1, sizeof(char *));
	ag->out_fd = -1;
	ag->in_fd = -1;
	ag->here_flag = 0;
	ag->heredoc_fd = -1;
	ag->next = NULL;
}
