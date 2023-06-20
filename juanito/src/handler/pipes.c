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

void handle_pipes(t_shell *args)
{
    int stdin_copy = dup(STDIN_FILENO);
    int stdout_copy = dup(STDOUT_FILENO);
    FILE *fd_in = fdopen(stdin_copy, "r");
    FILE *fd_out = fdopen(stdout_copy, "w");

    t_comand *current = args->token;
    while (current != NULL)
    {
        int pipefd[2];
        if (pipe(pipefd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) // Child process
        {
            close(pipefd[0]); // Close unused read end

            // Set up input redirection
            if (dup2(fileno(fd_in), STDIN_FILENO) == -1)
            {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            fclose(fd_in);

            // Set up output redirection if there is a subsequent command
            if (current->next != NULL)
            {
                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
                {
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }
            close(pipefd[1]);

            // Execute the command
            if (!ft_strncmp(current->cmd, "echo", 4))
            {
                // Execute the echo command
                if (execlp("echo", "echo", current->argm[1], NULL) == -1)
                {
                    perror("execlp");
                    exit(EXIT_FAILURE);
                }
            }
            else if (args->input[0] == '.' && args->input[1] == '/')
                open_exec(args);
            else if (args->input[0] == '/')
                open_exec_abs(args);
            else
            {
                // Execute the command
                if (execvp(current->cmd, current->argm) == -1)
                {
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else // Parent process
        {
            close(pipefd[1]); // Close unused write end

            // Set the next command's input to be the current command's output
            fd_in = fdopen(pipefd[0], "r");

            // Wait for the child process to complete
            if (waitpid(pid, NULL, 0) == -1)
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            // Read the output from the child process
            char buffer[1024];
            ssize_t nread;
            while ((nread = fread(buffer, sizeof(char), sizeof(buffer), fd_in)) > 0)
            {
                fwrite(buffer, sizeof(char), nread, fd_out);
            }
        }

        current = current->next;
    }

    // Restore original stdin and stdout
    dup2(stdin_copy, STDIN_FILENO);
    dup2(stdout_copy, STDOUT_FILENO);
    close(stdin_copy);
    close(stdout_copy);
    fclose(fd_in);
    fclose(fd_out);
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
