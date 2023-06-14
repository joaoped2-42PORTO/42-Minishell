/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:24:57 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/13 15:59:08 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_comand	*init(t_shell *args, int *i)
{
	t_comand	*ag;
	int			j;

	j = 0;
	ag = malloc(sizeof(t_comand));

	if (!ag)
		return (NULL);
	ag->argm = ft_calloc(see_split_size(args), sizeof(char *));
	ag->pipe_dir = ft_calloc(3, sizeof(char));
	ag->next = NULL;
	ag->cmd = ft_strdup(args->split[(*i)++]);
	while (args->split[*i] && args->split[*i][0] != '|')
		ag->argm[j++] = ft_strdup(args->split[(*i)++]);
	if (args->split[*i] && args->split[*i][0] == '|')
		ag->pipe_dir = ft_strdup(args->split[*i]);
	ag->next = NULL;
	return (ag);
}


t_comand	*init_token(t_shell *args)
{
	int			i;
	t_comand	*tmp;

	args->split = split_db_quotes(args->input, ' ');
	change_split(args);
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
