/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:24:57 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/13 12:47:51 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_comand	*init(t_shell *args)
{
	t_comand	*ag;

	ag = malloc(sizeof(t_comand));
	if (!ag)
		return (NULL);
	ag->cmd = ft_calloc(ft_strlen(args->input), sizeof(char));
	ag->argm = ft_calloc(ft_strlen(args->input), sizeof(char));
	ag->pipe_dir = ft_calloc(3, sizeof(char));
	ag->next = NULL;
	return (ag);
}

void	token_helper(t_shell *args, int *i, int *j, t_comand *tmp)
{
	*j = 0;
	while (!ft_isalnum(args->input[*i]))
		(*i)++;
	while (args->input[*i] && args->input[*i] != ' ')
		tmp->cmd[(*j)++] = args->input[(*i)++];
	while (args->input[*i] && !ft_isalnum(args->input[*i]))
		(*i)++;
	if (args->input[*i] == '\0')
		return ;
	*j = 0;
	while (args->input[*i] && !ft_isalnum(args->input[*i]))
		(*i)++;
	while (args->input[*i]
		&& check_pipe_rede(args->input[*i], args->input[*i + 1]))
		tmp->argm[(*j)++] = args->input[(*i)++];
	*j = 0;
	if (args->input[*i] != '\0')
	{
		if (!check_pipe_rede(args->input[*i], args->input[*i + 1]))
			add_bottom(&args->token, init(args));
		while (args->input[*i] != ' ' && !ft_isalnum(args->input[*i]))
			args->token->pipe_dir[(*j)++] = args->input[(*i)++];
	}
}

void	init_token(t_shell *args)
{
	int			i;
	int			j;
	t_comand	*tmp;

	tmp = args->token;
	j = 0;
	i = 0;
	while (args->input[i])
	{
		token_helper(args, &i, &j, tmp);
		tmp = tmp->next;
	}
}

void	init_values(t_shell *args, char	**env, int i)
{
	args->index = 0;
	args->env = ft_calloc(sizeof(char *), i + 1);
	args->path = ft_calloc(1, sizeof(char));
	alloc_env_mem(env, args->env);
	get_path_struct(args);
	config_signals();
	args->exit_status = 127;
}
