/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:06:47 by user              #+#    #+#             */
/*   Updated: 2023/07/11 23:27:48 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	handlefirstpipe(t_comand *token, t_shell *args, int *fd)
{
	handle_redir132(args);
	if (args->token->out_fd == -1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror("dup2: ");
		close(fd[1]);
	}
	if (args->token->cmd[0] == '\0')
		return ;
	if (args->flag != -2)
		forknbt(args, token, fd);
	if (args->token->out_fd != -1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror("dup2: ");
		close(fd[1]);
	}
}

void	handlemidpipes(t_comand *token, t_shell *args, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	pipe(fd);
	handle_redir132(args);
	if (args->token->out_fd == -1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (args->flag != -2)
		forknbt(args, token, fd);
	if (args->token->out_fd != -1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror("dup2: ");
		close(fd[1]);
	}
}

void	handlelastpipes(t_comand *token, t_shell *args, int *fd)
{
	handle_redir132(args);
	if (args->token->out_fd == -1)
	{
		dup2(args->out, STDOUT_FILENO);
		close(args->out);
	}
	if (args->token->in_fd == -1)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (args->flag != -2)
			forknbt(args, token, fd);
	}
	else
	{
		if (args->flag != -2)
			forknbt(args, token, fd);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	close_redirection(args);
	dup2(args->in, STDIN_FILENO);
	close(args->in);
}

void	execpipes(t_comand *token, t_shell *args, int *fd, int *k)
{
	if (*k == 0)
	{
		args->flag = 0;
		args->in = dup(STDIN_FILENO);
		args->out = dup(STDOUT_FILENO);
		args->stdin_here = dup(STDIN_FILENO);
		args->stdout_here = dup(STDOUT_FILENO);
		handlefirstpipe(token, args, fd);
	}
	else if (*k != args->list_size - 1)
	{
		args->flag = 0;
		handlemidpipes(token, args, fd);
	}
	else if (*k == args->list_size - 1)
	{
		args->flag = 0;
		handlelastpipes(token, args, fd);
	}
}

void	pipes(t_comand *token, t_shell *args)
{
	int	fd[2];

	args->list_size = checklistsizeforpipes(token);
	if (args->heredoc)
		wait(0);
	pipe(fd);
	pipesloop(token, args, fd);
	waitpid(-1, &g_status, 0);
	while (waitpid(-1, &g_status, 0) > 0)
		continue ;
	if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
	signal(SIGINT, new_prompt);
}
