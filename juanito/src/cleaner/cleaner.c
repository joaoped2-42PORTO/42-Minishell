/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:45:54 by huolivei          #+#    #+#             */
/*   Updated: 2023/05/29 11:40:47 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_env_size(char **str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

void	free_split(t_shell *args)
{
	int	i;

	i = -1;
	while (args->split[++i])
		free(args->split[i]);
	free(args->split);
}

void	free_list(t_shell *args)
{
	t_comand *tmp;

	while (args->token)
	{
		tmp = args->token->next;
		free(args->token->cmd);
		free(args->token->argm);
		free(args->token->pipe_dir);
		free(args->token);
		args->token = tmp;
	}
}

void	do_exit(t_shell *args)
{
	int	i;

	i = -1;
	while (args->split[++i])
		free(args->split[i]);
	free(args->split);
	i = -1;
	while (args->env[++i] != 0)
		free(args->env[i]);
	free(args->env);
	free(args->path);
	free(args);
	rl_clear_history();
	exit (0);
}

void	do_small_exit(t_shell *args)
{
	int	i;

	i = -1;
	while (args->env[++i] != 0)
		free(args->env[i]);
	free(args->env);
	free(args->path);
	free(args);
	rl_clear_history();
	exit (0);
}
