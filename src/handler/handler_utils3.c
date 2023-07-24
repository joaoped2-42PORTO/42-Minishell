/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:56:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/25 00:14:13 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_input(t_shell *args, int *i)
{
	(*i)++;
	if (!check_for_first_redir(args->token->redir, i))
	{
		printf("Too many redirs!\n");
		g_status = 2;
		return (0);
	}
	args->token->in_fd = open(args->token->redir[*i], O_RDONLY);
	if (args->token->in_fd == -1)
	{
		args->flag = -2;
		perror("bash");
		g_status = 1;
		return (0);
	}
	else
		dup2(args->token->in_fd, STDIN_FILENO);
	return (1);
}

int	handle_output(t_shell *args, int *i)
{
	(*i)++;
	if (!check_for_first_redir(args->token->redir, i))
	{
		printf("Too many redirs!\n");
		g_status = 2;
		return (0);
	}
	args->token->out_fd = open(args->token->redir[*i],
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (args->token->out_fd == -1)
	{
		args->flag = -2;
		perror("bash");
		g_status = 1;
		return (0);
	}
	else
		dup2(args->token->out_fd, STDOUT_FILENO);
	return (1);
}

int	handle_append(t_shell *args, int *i)
{
	(*i)++;
	if (!check_for_first_redir(args->token->redir, i))
	{
		printf("Too many redirs!\n");
		g_status = 2;
		return (0);
	}
	args->token->out_fd = open(args->token->redir[*i],
			O_APPEND | O_CREAT | O_RDWR, 0644);
	if (args->token->out_fd == -1)
	{
		args->flag = -2;
		perror("bash");
		g_status = 1;
		return (0);
	}
	else
		dup2(args->token->out_fd, STDOUT_FILENO);
	return (1);
}

int	handle_redir(t_shell *args)
{
	int	i;

	i = 0;
	while (args->token->redir[i])
	{
		if (args->token->redir[i][0] == '>' && args->token->redir[i][1] == '>')
		{
			if (!handle_append(args, &i))
				return (0);
		}
		else if (args->token->redir[i][0] == '<'
			&& args->token->redir[i][1] == '<')
		{
			if (!handle_heredoc(args, &i))
				return (0);
		}
		if (!redirs_helper(args, &i))
			return (0);
		i++;
	}
	return (1);
}

void	start_heredoc(t_shell *args, int i)
{
	char	*buffer;
	int		fd;
	char	*tmp;

	tmp = NULL;
	args->pid = fork();
	if (args->pid == 0)
	{
		here_doc_utils(args, &fd);
		config_signals2();
		while (1)
		{
			buffer = readline("heredoc >");
			if (!check_for_null(buffer))
				child_exit(args);
			if (str_is_equal(buffer, args->token->redir[i]))
				child_exit(args);
			tmp = heredoc_expander_starter(tmp, args, buffer);
			heredoc_expander_utils(buffer, tmp, fd);
		}
		free(buffer);
		close(fd);
	}
	heredoc_signals(args);
}
