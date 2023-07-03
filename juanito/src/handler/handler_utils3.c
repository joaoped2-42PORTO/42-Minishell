/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:56:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/03 23:13:16 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_input(t_shell *args, int *i)
{
	(*i)++;
	if (args->token->in_fd != -1)
		close(args->token->out_fd);
	args->token->in_fd = open(args->token->redir[*i], O_RDONLY, 0777);
	if (args->token->in_fd == -1)
		perror("open");
	dup2(args->token->in_fd, STDIN_FILENO);
}

void	handle_output(t_shell *args, int *i)
{
	(*i)++;
	if (args->token->out_fd != -1)
		close(args->token->out_fd);
	args->token->out_fd = open(args->token->redir[*i],
			O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (args->token->out_fd == -1)
		perror("open");
	dup2(args->token->out_fd, STDOUT_FILENO);
}

void	handle_append(t_shell *args, int *i)
{
	(*i)++;
	if (args->token->out_fd != -1)
		close(args->token->out_fd);
	args->token->out_fd = open(args->token->redir[*i],
			O_APPEND | O_CREAT | O_RDWR, 0777);
	if (args->token->out_fd == -1)
		perror("open");
	dup2(args->token->out_fd, STDOUT_FILENO);
}

void	handle_redir(t_shell *args)
{
	int	i;

	i = 0;
	while (args->token->redir[i])
	{
		if (args->token->redir[i][0] == '>' && args->token->redir[i][1] == '>')
			handle_append(args, &i);
		else if (args->token->redir[i][0] == '<' && args->token->redir[i][1] == '<')
			handle_heredoc(args, &i);
		else if (args->token->redir[i][0] == '>')
			handle_output(args, &i);
		else if (args->token->redir[i][0] == '<')
			handle_input(args, &i);
		i++;
	}
}

void	start_heredoc(t_shell *args, int *i)
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
