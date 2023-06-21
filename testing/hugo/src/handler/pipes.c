/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:06:47 by user              #+#    #+#             */
/*   Updated: 2023/06/21 21:42:25 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int pipes(t_comand *token, t_shell *args) {
    int i = 0;
    int k = 0;
    int pid, status;
    int x = 0;
    int fd[2];
    int next_fd[2];  // Declaration added
    t_comand *curr = token;

    while (curr != NULL) {
        i++;
        curr = curr->next;
    }

    if (i == 0)
        return 0;

    char *path;
    char **path_split;
    
    while (k < i) {
        if (k != 0)
            token = token->next;
        
        path = get_path(args);
        
        if (path) {
            path_split = ft_split(path, ':');
            free(path);
            path = get_acess(path_split, token);
        } else {
            return 0;
        }
        
        pipe(fd);
        pid = fork();
        
        if (pid == 0 && x == 0) {
            char *ptr[] = {"ls", "-l", NULL};
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            execve(path, ptr, NULL);
            perror("execve");
            exit(EXIT_FAILURE);
        } else if (pid == 0 && k != i - 1) {
            char *ptr[] = {"grep", "u", NULL};
            close(fd[1]);
            pipe(next_fd);
            close(next_fd[0]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            dup2(next_fd[1], STDOUT_FILENO);
            close(next_fd[1]);
            execve(path, ptr, NULL);
            perror("execve");
            exit(EXIT_FAILURE);
            x++;
        } else {
            char *ptr[] = {"wc", "-l", NULL};
            close(fd[0]);
            close(fd[1]);
            dup2(next_fd[0], STDIN_FILENO);
            close(next_fd[0]);
            execve(path, ptr, NULL);
        }
        
        wait(&status);
        free(path);
        k++;
    }
    
    close(next_fd[0]);
    printf("The size of the list is %d \n", i);
    return 0;
}