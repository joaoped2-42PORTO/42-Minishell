/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:02:23 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/07 17:34:10 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_rd2(t_shell *args, t_comand *ag, int *i, int *x)
{
	if (args->split[*i][0] == '>')
	{
		if (!args->split[(*i) + 1])
			return ;
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->flag = 1;
	}
	else if (args->split[*i][0] == '<')
	{
		if (!args->split[(*i) + 1])
			return ;
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
		if (!args->split[(*i) + 1])
			return ;
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->flag = 1;
	}
	else if (args->split[*i][0] == '<' && args->split[*i][1] == '<')
	{
		if (!args->split[(*i) + 1])
			return ;
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->flag = 1;
	}
	else
		check_rd2(args, ag, i, x);
}

void	inithpl(t_shell *args, t_comand *ag, int *i, int *x)
{
	int	j;

	j = 0;
	ag->argm[j++] = ft_strdup(args->split[*i]);
	ag->cmd = ft_strdup(args->split[(*i)++]);
	while (args->split[*i] && !checkpipered(args, i))
	{
		check_rd(args, ag, i, x);
		if (args->split[*i] && !checkpipered(args, i)
			&& check_for_first_redir(args->split, i)
			&& ft_strlen(args->split[*i]) > 0)
			ag->argm[j++] = ft_strdup(args->split[(*i)++]);
		else
			(*i)++;
	}
}
