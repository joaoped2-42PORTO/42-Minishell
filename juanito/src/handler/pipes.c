/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:06:47 by user              #+#    #+#             */
/*   Updated: 2023/07/03 17:23:07 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handlefirstpipe(t_comand *token, t_shell *args, int *fd)
{
	int		pid;
	char	*path;

	path = returncompletepath(token, args);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (isbuiltin(token, args) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(path, token->argm, NULL) != 0)
			{
				perror("Error");
				args->exit_status = 126;
				exit(126);
			}
		}
		waitpid(-1, NULL, 0);
	}
	free(path);
}

void	handlemidpipes(t_comand *token, t_shell *args, int *fd)
{
	int		pid;
	char	*path;

	path = returncompletepath(token, args);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	pipe(fd);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (isbuiltin(token, args) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(path, token->argm, NULL) != 0)
			{
				perror("Error");
				args->exit_status = 126;
				exit(126);
			}
		}
		waitpid(-1, NULL, 0);
	}
	free(path);
}

void	handlelastpipes(t_comand *token, t_shell *args, int *fd)
{
	int		pid;
	char	*path;

	path = returncompletepath(token, args);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(args->out, STDOUT_FILENO);
	close(args->out);
	if (isbuiltin(token, args) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(path, token->argm, NULL) != 0)
			{
				perror("Error");
				args->exit_status = 126;
				exit(126);
			}
		}
		waitpid(-1, NULL, 0);
	}
	free(path);
	dup2(args->in, STDIN_FILENO);
	close(args->in);
}

void	execpipes(t_comand *token, t_shell *args, int *fd, int *k)
{
	if (*k == 0)
	{
		args->in = dup(STDIN_FILENO);
		args->out = dup(STDOUT_FILENO);
		handlefirstpipe(token, args, fd);
	}
	else if (*k != args->list_size - 1)
		handlemidpipes(token, args, fd);
	else if (*k == args->list_size - 1)
		handlelastpipes(token, args, fd);
}

void	pipes(t_comand *token, t_shell *args)
{
	int			k;
	int			fd[2];
	t_comand	*ptr;

	args->list_size = checklistsizeforpipes(token);
	k = 0;
	pipe(fd);
	while (k < args->list_size)
	{
		if (k != 0)
		{
			ptr = token->next;
			free(token->cmd);
			free_matrix(token->argm);
			free_matrix(token->redir);
			free(token);
			token = ptr;
			args->token = token;
		}
		execpipes(token, args, fd, &k);
		k++;
	}
}
