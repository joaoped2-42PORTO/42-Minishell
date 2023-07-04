/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:24:57 by huolivei          #+#    #+#             */
/*   Updated: 2023/07/04 23:58:25 by huolivei         ###   ########.fr       */
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
		if (args->split[*i][0] == '>')
			(*i)++;
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
	ag = malloc(sizeof(t_comand));
	if (!ag)
		return (NULL);
	ag->argm = ft_calloc(see_split_size(args) + 1, sizeof(char *));
	ag->redir = ft_calloc(see_split_size(args) + 1, sizeof(char *));
	ag->next = NULL;
	if (!check_for_first_redir(args->split, i))
		check_redir(args, ag, i, &x);
	if (!args->split[*i] || checkpipered(args, i))
	{
		ag->cmd = ft_calloc(1, 1);
		return (ag);
	}
	ag->argm[j++] = ft_strdup(args->split[*i]);
	ag->cmd = ft_strdup(args->split[(*i)++]);
	while (args->split[*i] && !checkpipered(args, i))
	{
		check_redir(args, ag, i, &x);
		if (args->split[*i] && !checkpipered(args, i))
			ag->argm[j++] = ft_strdup(args->split[(*i)++]);
	}
	return (ag);
}

void	sort_exp(t_shell *args)
{
	int	i;
	int	j;
	int	x;
	char	*tmp;

	x = 1;
	i = -1;
	while (args->exp[++i])
	{
		if (!args->exp[x])
			break;
		j = 0;
		while (args->exp[i][j] == args->exp[x][j])
			j++;
		if (args->exp[i][j] > args->exp[x][j])
		{
			tmp = args->exp[i];
			args->exp[i] = args->exp[x];
			args->exp[x] = tmp;
			i = -1;
			x = 0;
		}
		x++;
	}
}

t_comand	*init_token(t_shell *args)
{
	int			i;
	t_comand	*tmp;

	args->heredoc = 0;
	sort_exp(args);
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
	args->env = ft_calloc(sizeof(char *), i + 1);
	args->exp = ft_calloc(sizeof(char *), i + 1);
	args->path = ft_calloc(1, sizeof(char));
	alloc_env_mem(env, args->env, args->exp);
	get_path_struct(args);
	config_signals();
	args->exit_status = 127;
}
