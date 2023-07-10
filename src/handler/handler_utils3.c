/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neddy <neddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:56:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/10 11:31:12 by neddy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_input(t_shell *args, int *i)
{
	(*i)++;
	args->token->in_fd = open(args->token->redir[*i], O_RDONLY, 0777);
	if (args->token->in_fd == -1)
		perror("open");
	args->flag = 1;
	dup2(args->token->in_fd, STDIN_FILENO);
}

void	handle_output(t_shell *args, int *i)
{
	(*i)++;
	args->token->out_fd = open(args->token->redir[*i],
			O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (args->token->out_fd == -1)
		perror("open");
	args->flag = 1;
	dup2(args->token->out_fd, STDOUT_FILENO);
}

void	handle_append(t_shell *args, int *i)
{
	(*i)++;
	args->token->out_fd = open(args->token->redir[*i],
			O_APPEND | O_CREAT | O_RDWR, 0777);
	if (args->token->out_fd == -1)
		perror("open");
	args->flag = 1;
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
		else if (args->token->redir[i][0] == '<'
			&& args->token->redir[i][1] == '<')
			handle_heredoc(args, &i);
		else if (args->token->redir[i][0] == '>')
			handle_output(args, &i);
		else if (args->token->redir[i][0] == '<')
			handle_input(args, &i);
		i++;
	}
}

/* void	start_heredoc(t_shell *args, int i)
{
	char	*buffer;
	int		fd;
	char	*tmp;
	int		flag;

	flag = 1;
	tmp = NULL;
	here_doc_utils(args, &fd);
	while (1)
	{
		buffer = readline("heredoc >");
		if (!check_for_null(buffer))
			break ;
		if (str_is_equal(buffer, args->token->redir[i]))
			break ;
		if (ft_strchr(buffer, '$'))
			tmp = heredoc_expander_starter(&flag, tmp, args, buffer);
		if (flag == 0)
			heredoc_expander_utils(buffer, tmp, fd);
		else
			heredoc_nonexpander_utils(buffer, fd);
	}
	free(buffer);
	close(fd);
} */

void	start_heredoc(t_shell *args, int i)
{
	char	*buffer;
	int		fd;
	char	*tmp;

	tmp = NULL;
	here_doc_utils(args, &fd);
	while (1)
	{
		buffer = readline("heredoc >");
		if (!check_for_null(buffer))
			break ;
		if (str_is_equal(buffer, args->token->redir[i]))
			break ;
		tmp = heredoc_expander_starter(tmp, args, buffer);
		heredoc_expander_utils(buffer, tmp, fd);
	}
	free(buffer);
	close(fd);
}
