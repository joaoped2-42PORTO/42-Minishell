/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:03:15 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/08 17:28:48 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
