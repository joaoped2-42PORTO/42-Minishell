/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:06:47 by user              #+#    #+#             */
/*   Updated: 2023/07/08 17:35:58 by joaoped2         ###   ########.fr       */
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
		else if (args->token->redir[i][0] == '<' && args->token->redir[i][1] == '\0')
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
		if (args->token->redir[i][0] == '<'
			&& args->token->redir[i][1] == '<')
				handle_heredoc(args, &i);
		i++;
	}
}

void	handlefirstpipe(t_comand *token, t_shell *args, int *fd)
{
	see_heredoc(args);
	if (args->heredoc)
		wait(0);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("dup2: ");
	close(fd[1]);
	//handle_redir(args);
	handle_redir_pipes(args);
	if (args->token->cmd[0] == '\0')
		return ;
	forknbt(args, token, fd);
}

void	handlemidpipes(t_comand *token, t_shell *args, int *fd)
{
	if (args->heredoc)
		wait(0);
	see_heredoc(args);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	pipe(fd);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	//handle_redir(args);
	handle_redir_pipes(args);
	forknbt(args, token, fd);
}

void	handlelastpipes(t_comand *token, t_shell *args, int *fd)
{
	if (args->heredoc)
		wait(0);
	see_heredoc(args);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	//handle_redir(args);
	handle_redir_pipes(args);
	if (args->flag != 1)
	{
		dup2(args->out, STDOUT_FILENO);
		close(args->out);
	}
	forknbt(args, token, fd);
	close_redirection(args);
	if (args->flag != 1)
	{
		dup2(args->in, STDIN_FILENO);
		close(args->in);
	}
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
		handlemidpipes(token, args, fd);
	else if (*k == args->list_size - 1)
		handlelastpipes(token, args, fd);
}

void	pipes(t_comand *token, t_shell *args)
{
	int			fd[2];

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
