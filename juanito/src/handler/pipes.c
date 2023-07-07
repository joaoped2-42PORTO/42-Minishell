/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:06:47 by user              #+#    #+#             */
/*   Updated: 2023/07/07 13:54:00 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	start_here_doc(t_shell *args, int *i)
{
	char	*buffer;
	int		fd;

	fd = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
		perror("open");
	while (1)
	{
		buffer = readline("heredoc >");
		if (buffer == NULL)
		{
			perror("heredoc");
			break ;
		}
		if (str_is_equal(buffer, args->token->redir[*i]))
			break ;
		ft_putendl_fd(buffer, fd);
		free(buffer);
	}
	free(buffer);
	close(fd);
}

void	_handle_here_doc(t_comand *args, int *i, t_shell *token)
{
	(*i)++;
	if (args->in_fd != -1)
		close(args->out_fd);
	token->heredoc = 1;
	start_here_doc(token, i);
	args->in_fd = open("heredoc", O_RDONLY);
	if (args->in_fd == -1)
		perror("open");
	dup2(token->token->in_fd, STDIN_FILENO);
	token->heredoc = 0;
}

void	handle_here_doc(t_comand *args, t_shell *token, int *flag)
{
	int	i;

	i = 0;
	if (args->flag == 1)
	{
		if (args->redir[0][0] == '<' && args->redir[0][1] == '<')
		{
			*flag = 1;
			_handle_here_doc(args, &i, token);
		}
	}
}

void	handlefirstpipe(t_comand *token, t_shell *args, int *fd)
{
	char	*path;
	int		pid;
	int		res;

	res = 0;
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("dup2: ");
	path = returncompletepath(token, args);
	close(fd[1]);
	handle_redir(args);
	if (args->token->cmd[0] == '\0')
		return ;
	res = isbuiltin(token, args);
	if (res == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			close(fd[0]);
			do_non_builtinsforpipes(args, path);
		}
		signal(SIGINT, new_prompt);
	}
	free(path);
}

void	handlemidpipes(t_comand *token, t_shell *args, int *fd)
{
	char	*path;
	int		pid;
	int		res;

	res = 0;
	if (args->heredoc)
		wait(0);
	path = returncompletepath(token, args);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	pipe(fd);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	handle_redir(args);
	res = isbuiltin(token, args);
	if (res == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			close(fd[0]);
			do_non_builtinsforpipes(args, path);
		}
		signal(SIGINT, new_prompt);
	}
	free(path);
}

void	handlelastpipes(t_comand *token, t_shell *args, int *fd)
{
	char	*path;
	int		pid;
	int		res;

	res = 0;
	if (args->heredoc)
		wait(0);
	path = returncompletepath(token, args);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	handle_redir(args);
	if (args->flag != 1)
	{
		dup2(args->out, STDOUT_FILENO);
		close(args->out);
	}
	res = isbuiltin(token, args);
	if (res == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			close(fd[0]);
			do_non_builtinsforpipes(args, path);
		}
		signal(SIGINT, new_prompt);
	}
	free(path);
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
	if (args->heredoc)
		wait(0);
	pipe(fd);
	while (k < args->list_size)
	{
		if (k != 0)
		{
			args->flag = 0;
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
	waitpid(-1, &g_status, 0);
	while (waitpid(-1, &g_status, 0) > 0)
		continue ;
	if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
	signal(SIGINT, new_prompt);
}
