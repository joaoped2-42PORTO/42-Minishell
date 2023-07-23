/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:38:33 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/23 15:24:04 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	first_redir(t_shell *args, char *str, t_comand *tmp)
{
	if (args->split[args->index])
	{
		if (args->split[args->index][0] == '<'
			|| args->split[args->index][0] == '>')
			lexer_redir(str, args, tmp);
		init_lexer(str, args, tmp);
	}
}

int	check_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

void	replace_stds(t_shell *args)
{
	dup2(args->in, STDIN_FILENO);
	dup2(args->out, STDOUT_FILENO);
}

void	args_in_exp(void)
{
	printf("No arguments allowed\n");
	g_status = 2;
	return ;
}

void	handler_init(t_shell *args)
{
	args->flag = 0;
	args->out = dup(STDOUT_FILENO);
	args->in = dup(STDIN_FILENO);
}
