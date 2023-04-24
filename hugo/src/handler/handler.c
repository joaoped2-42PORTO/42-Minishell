/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/24 17:01:47 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
    char *path = getenv("PATH");
    char *dir = strtok(path, ":");
    char ls_path[256];

    while (dir != NULL) {
        sprintf(ls_path, "%s/ls", dir);
        if (access(ls_path, X_OK) == 0) {
            printf("Found ls command at %s\n", ls_path);
            break;
        }
        dir = strtok(NULL, ":");
    }
*/



void	clearcmd()
{
	int pid;
	char *args[] = {"clear", NULL};

	if ((pid = fork()) == 0)
		execv("/usr/bin/clear", args);
	waitpid(-1, NULL, 0);
}

void	lscmd(t_shell *args)
{
	int	pid;
	//char	*path = getenv("PATH");

	if ((pid = fork()) == 0)
	{
    		if(execv("/bin/ls", args->split) != 0)
			{
				perror("Error\n");
				return ;
			}
	}
	waitpid(-1, NULL, 0);
}

int	cmdhandler(t_shell *args)
{
	if (!ft_strncmp(args->input, "pwd", 3))
		check_pwd();
	else if (!ft_strncmp(args->input, "cd ", 3))
		do_cd(args->input);
	else if (!ft_strncmp(args->input, "cd", 2))
		chdir(getenv("HOME"));
	else if (!ft_strncmp(args->input, "exit", 4))
		return (0);
	else if (!ft_strncmp(args->input, "clear", 5))
		clearcmd();
	else if (!ft_strncmp(args->input, "ls ", 2))
		lscmd(args);
	else
		printf("command not found: %s\n", args->input);
	return(1);
}
