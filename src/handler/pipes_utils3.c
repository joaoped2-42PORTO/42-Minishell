/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:44:47 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/13 19:44:56 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	nr_higher(t_shell *args)
{
	g_status = 2;
	printf("%s: %s: numeric argument required\n", args->token->cmd,
		args->token->argm[1]);
	free_split(args);
	free_list(args);
	do_small_exit(args);
}

void	nr_higher_pipes(t_shell *args)
{
	g_status = 2;
	printf("%s: %s: numeric argument required\n", args->token->cmd,
		args->token->argm[1]);
}

int	many_args(t_shell *args)
{
	if (args->token->argm[2])
	{
		printf("%s: too many arguments\n", args->token->cmd);
		g_status = 1;
		return (1);
	}
	return (0);
}

int	handle_redir132(t_shell *args)
{
	int	i;

	i = 0;
	while (args->token->redir[i])
	{
		if (args->token->redir[i][0] == '>' && args->token->redir[i][1] == '>')
			handle_append(args, &i);
		else if (args->token->redir[i][0] == '<'
			&& args->token->redir[i][1] == '<')
			handle_heredoc(args, &i);
		else if (args->token->redir[i][0] == '>')
			handle_output(args, &i);
		else if (args->token->redir[i][0] == '<')
			handle_input(args, &i);
		i++;
	}
	return (0);
}
