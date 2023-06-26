/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:24:57 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/26 14:13:57 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checkPipeRed(t_shell *args, int *i)
{
	if (args->split[*i][0] == '|')
		return (1);
	return (0);
}

t_comand	*init(t_shell *args, int *i)
{
	t_comand	*ag;
	int			j;
	int			x;
	int			z;
	int			a;

	a = 0;
	z = 0;
	j = 0;
	x = 0;
	ag = malloc(sizeof(t_comand));
	if (!ag)
		return (NULL);
	ag->argm = ft_calloc(see_split_size(args) + 1, sizeof(char *));
	ag->out_red = ft_calloc(see_split_size(args) + 1, sizeof(char *));
	ag->in_red = ft_calloc(see_split_size(args) + 1, sizeof(char *));
	ag->app_red = ft_calloc(see_split_size(args) + 1, sizeof(char *));
	//ag->pipe_dir = NULL;
	ag->argm[j++] = ft_strdup(args->split[*i]);
	//ag->flags[x++] = ft_strdup(args->split[*i]);
	ag->cmd = ft_strdup(args->split[(*i)++]);
	while (args->split[*i] && !checkPipeRed(args, i))
	{
		if (args->split[*i][0] == '>' && args->split[*i][1])
		{
			(*i)++;
			ag->app_red[a++] = ft_strdup(args->split[(*i)++]);
		}
		else if (args->split[*i][0] == '>')
		{
			args->nr_red++;
			(*i)++;
			ag->out_red[x++] = ft_strdup(args->split[(*i)++]);
		}
		else if (args->split[*i][0] == '<')
		{
			args->nr_red++;
			(*i)++;
			ag->in_red[z++] = ft_strdup(args->split[(*i)++]);
		}
		else if (args->split[*i])
			ag->argm[j++] = ft_strdup(args->split[(*i)++]);
	}
	/* ag->argm[j] = 0;
	if (args->split[*i] && checkPipeRed(args, i))
		ag->pipe_dir = ft_strdup(args->split[*i]); */
	ag->next = NULL;
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
		if(i == 0)
			tmp = init(args, &i);
		else
			add_bottom(&tmp, init(args, &i));
		if (args->split[i])
			i++;
	}
	return (tmp);
}

void	init_values(t_shell *args, char	**env, int i)
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
