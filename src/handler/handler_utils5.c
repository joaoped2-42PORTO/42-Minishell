/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:20:58 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/25 00:11:40 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc_utils(t_shell *args, int *fd)
{
	int	fd1;

	if (args->token->in_fd != -1)
		close (args->token->in_fd);
	if (args->token->out_fd != -1)
		close (args->token->out_fd);
	dup2(args->out, STDOUT_FILENO);
	dup2(args->in, STDIN_FILENO);
	fd1 = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd1 < 0)
		perror("open");
	*fd = fd1;
}

void	heredoc_expander_utils(char *buffer, char *tmp, int fd)
{
	free(buffer);
	buffer = ft_strdup(tmp);
	free(tmp);
	ft_putendl_fd(buffer, fd);
	free(buffer);
}

void	heredoc_nonexpander_utils(char *buffer, int fd)
{
	ft_putendl_fd(buffer, fd);
	free(buffer);
}

char	*heredoc_expander_starter(char *tmp, t_shell *args, char *buffer)
{
	tmp = print_env_var2(args, buffer);
	return (tmp);
}

void	heredoc_signals(t_shell *args)
{
	signal(SIGINT, new_prompt);
	waitpid(args->pid, &g_status, 0);
	config_signals();
}
