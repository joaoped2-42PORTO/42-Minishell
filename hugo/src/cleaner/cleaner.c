/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:45:54 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/22 22:36:29 by huolivei         ###   ########.fr       */
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

int	free_split(t_shell *args)
{
	int	i;

	i = -1;
	while (args->split[++i])
		free(args->split[i]);
	free(args->split);
	return (0);
}

int	free_list(t_shell *args)
{
	t_comand *tmp;

	while (args->token)
	{
		tmp = args->token->next;
		free(args->token->cmd);
		free_matrix(args->token->argm);
		free_matrix(args->token->out_red);
		free_matrix(args->token->in_red);
		free_matrix(args->token->app_red);
		//free(args->token->pipe_dir);
		free(args->token);
		args->token = tmp;
	}
	free (args->token);
	free (tmp);
	return (0);
}

void	do_exit(t_shell *args)
{
	free_split(args);
	free_matrix(args->env);
	free_matrix(args->exp);
	free_list(args);
	free(args->path);
	free(args->input);
	free(args);
	rl_clear_history();
	exit (0);
}

void	do_small_exit(t_shell *args)
{
	free_matrix(args->env);
	free_matrix(args->exp);
	free(args->path);
	free(args);
	rl_clear_history();
	exit (0);
}
