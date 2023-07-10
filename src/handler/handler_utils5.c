/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neddy <neddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:20:58 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/10 14:14:01 by neddy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc_utils(t_shell *args, int *fd)
{
	int	fd1;

	dup2(args->stdout_here, STDOUT_FILENO);
	dup2(args->stdin_here, STDIN_FILENO);
	fd1 = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd1 < 0) //if (*fd < 0)
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
