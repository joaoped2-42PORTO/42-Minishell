/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:44:47 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/09 10:51:43 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_redir_pipes(t_shell *args)
{
	int	i;

	i = 0;
	while (args->token->redir[i])
	{
		if (args->token->redir[i][0] == '>' && args->token->redir[i][1] == '>')
			handle_append(args, &i);
		else if (args->token->redir[i][0] == '>')
			handle_output(args, &i);
		else if (args->token->redir[i][0] == '<'
			&& args->token->redir[i][1] == '\0')
			handle_input(args, &i);
		i++;
	}
}

void	see_heredoc(t_shell *args)
{
	int	i;

	i = 0;
	while (args->token->redir[i])
	{
		if (args->token->redir[i][0] == '<' && args->token->redir[i][1] == '<')
			handle_heredoc(args, &i);
		i++;
	}
}

void	nr_higher(t_shell *args)
{
	g_status = 2;
	printf("%s: %s: numeric argument required\n", args->token->cmd,
		args->token->argm[1]);
	exit(g_status);
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
