/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:52:45 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/19 15:43:57 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_pipes(t_shell *args)
{
	
}
























/*
int	main(void)
{
	int	pipefd[2];

	pid_t ls_pid, cat_pid;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	ls_pid = fork();
	if (ls_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (ls_pid == 0)
	{                     // Child process for ls
		close(pipefd[0]); // Close unused read end
		// Redirect stdout to the write end of the pipe
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		// Execute ls command
		execlp("ls", "ls", NULL);
		perror("exec ls");
		exit(EXIT_FAILURE);
	}
	cat_pid = fork();
	if (cat_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (cat_pid == 0)
	{                     // Child process for cat
		close(pipefd[1]); // Close unused write end
		// Redirect stdin to the read end of the pipe
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		// Execute cat -e command
		execlp("cat", "cat", "-e", NULL);
		perror("exec cat");
		exit(EXIT_FAILURE);
	}
	// Parent process
	close(pipefd[0]);
	close(pipefd[1]);
	// Wait for child processes to complete
	waitpid(ls_pid, NULL, 0);
	waitpid(cat_pid, NULL, 0);
	return (0);
}
*/
