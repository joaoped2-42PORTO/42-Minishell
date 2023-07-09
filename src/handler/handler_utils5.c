/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:20:58 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/09 14:10:33 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc_utils(t_shell *args, int *fd)
{
	int	fd1;

	dup2(args->stdout_here, STDOUT_FILENO);
	dup2(args->stdin_here, STDIN_FILENO);
	fd1 = open("heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
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

char	*heredoc_expander_starter(int *flag, char *tmp,
									t_shell *args, char *buffer)
{
	*flag = 0;
	tmp = print_env_var2(args, buffer);
	return (tmp);
}
