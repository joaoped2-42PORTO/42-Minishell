/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:01:43 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/05 22:51:22 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc(t_shell *args, int *i)
{
	(*i)++;
	if (args->token->in_fd != -1)
		close(args->token->out_fd);
	args->heredoc = 1;
	start_heredoc(args, i);
	args->token->in_fd = open("heredoc", O_RDONLY);
	if (args->token->in_fd == -1)
		perror("open");
	dup2(args->token->in_fd, STDIN_FILENO);
	args->heredoc = 0;
}

void	execthenonbuiltin(t_shell *args, char *path)
{
	if (execve(path, args->token->argm, args->env) != 0)
	{
		printf("command not found: %s\n", args->token->cmd);
		g_status = 127;
		free(path);
		free_split(args);
		free_list(args);
		do_small_exit(args);
	}
}
