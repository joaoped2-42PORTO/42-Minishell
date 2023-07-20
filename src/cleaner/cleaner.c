/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:45:54 by huolivei          #+#    #+#             */
/*   Updated: 2023/07/20 23:00:14 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_env_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
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
	t_comand	*tmp;

	while (args->token)
	{
		tmp = args->token->next;
		free(args->token->cmd);
		free_matrix(args->token->argm);
		free_matrix(args->token->redir);
		free(args->token);
		args->token = tmp;
	}
	free(args->token);
	free(tmp);
	return (0);
}

void	do_exit(t_shell *args)
{
	(void)args;
	exit(g_status);
}

void	do_small_exit(t_shell *args)
{
	free_matrix(args->env);
	free_matrix(args->exp);
	free(args->input);
	free(args->path);
	free(args->pwd);
	free(args);
	rl_clear_history();
	exit(g_status);
}
