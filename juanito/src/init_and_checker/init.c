/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:24:57 by huolivei          #+#    #+#             */
/*   Updated: 2023/07/03 17:31:34 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_redir(t_shell *args, t_comand *ag, int *i, int *x)
{
	if (args->split[*i][0] == '>' && args->split[*i][1] == '>')
	{
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
	}
	else if (args->split[*i][0] == '<' && args->split[*i][1] == '<')
	{
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
	}
	else if (args->split[*i][0] == '>')
	{
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
	}
	else if (args->split[*i][0] == '<')
	{
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
		ag->redir[(*x)++] = ft_strdup(args->split[(*i)++]);
	}
}

int	check_for_first_redir(char **split, int *i)
{
	if (split[*i][0] == '>' && split[*i][1] == '>')
		return (0);
	else if (split[*i][0] == '<' && split[*i][1] == '<')
		return (0);
	else if (split[*i][0] == '>')
		return (0);
	else if (split[*i][0] == '<')
		return (0);
	return (1);
}

t_comand	*init(t_shell *args, int *i)
{
	t_comand	*ag;
	int			j;
	int			x;

	j = 0;
	x = 0;
	ag = malloc(sizeof(t_comand)); //leaks
	if (!ag)
		return (NULL);
	ag->argm = ft_calloc(see_split_size(args) + 1, sizeof(char *)); //leaks
	ag->redir = ft_calloc(see_split_size(args) + 1, sizeof(char *)); //leaks
	ag->next = NULL;
	if (!check_for_first_redir(args->split, i))
		check_redir(args, ag, i, &x);
	if (!args->split[*i])
	{
		ag->cmd = ft_calloc(1, 1);
		return (ag);
	}
	ag->argm[j++] = ft_strdup(args->split[*i]); //leaks
	ag->cmd = ft_strdup(args->split[(*i)++]); //leaks
	while (args->split[*i] && !checkpipered(args, i))
	{
		check_redir(args, ag, i, &x);
		if (args->split[*i])
			ag->argm[j++] = ft_strdup(args->split[(*i)++]);
	}
	return (ag);
}

t_comand	*init_token(t_shell *args)
{
	int			i;
	t_comand	*tmp;

	args->split = split_db_quotes(args->input);
	change_split(args);
	args->nr_red = 0;
	tmp = NULL;
	i = 0;
	while (args->split[i])
	{
		if (i == 0)
			tmp = init(args, &i);
		else
			add_bottom(&tmp, init(args, &i));
		if (args->split[i])
			i++;
	}
	tmp->in_fd = -1;
	tmp->out_fd = -1;
	return (tmp);
}

void	init_values(t_shell *args, char **env, int i)
{
	args->index = 0;
	args->env = ft_calloc(sizeof(char *), i + 1); //leaks
	args->exp = ft_calloc(sizeof(char *), i + 1); //leaks
	args->path = ft_calloc(1, sizeof(char));
	alloc_env_mem(env, args->env, args->exp);
	get_path_struct(args);
	config_signals();
	args->exit_status = 127;
}
