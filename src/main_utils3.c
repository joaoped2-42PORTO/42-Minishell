/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:38:33 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/20 23:12:04 by huolivei         ###   ########.fr       */
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
