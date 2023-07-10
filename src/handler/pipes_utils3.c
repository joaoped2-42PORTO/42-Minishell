/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:44:47 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/10 18:30:18 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_redir_pipes(t_shell *args)
{
	int	i;

	i = 0;
	while (args->token->redir[i])
	{
		if (args->token->redir[i][0] == '>' && args->token->redir[i][1] == '>')
		{
			handle_append(args, &i);
			return (1);
		}
		else if (args->token->redir[i][0] == '>')
		{
			handle_output(args, &i);
			return (1);
		}
/* 		else if (args->token->redir[i][0] == '<'
			&& args->token->redir[i][1] == '\0')
		{
			handle_input(args, &i);
			return (1);
		} */
		i++;
	}
	return (0);
}

int	see_heredoc(t_shell *args)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (args->token->redir[i])
	{
		if (args->token->redir[i][0] == '<' && args->token->redir[i][1] == '<')
		{
			handle_heredoc(args, &i);
			x = 1;
		}
		i++;
	}
	if (x == 1)
		return (1);
	return (0);
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
