/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/20 16:12:31 by joaoped2         ###   ########.fr       */
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

void	lscmd(char *input)
{
	char *path = getenv("PATH");
	char	*barra ="/";
	int pid;
	int i;
	int j;
	int k;
	char *args[] = {"ls", "-l", NULL};

	i = 0;
	j = 0;
	k = 0;
	while(path[i])
		i++;
	while(barra[k])
		path[i++] = barra[k++];
	while (input[j])
		path[i++] = input[j++];
	path[i] = '\0';

	//printf("%s\n", path);

	if (i == 2)
	{
		if ((pid = fork()) == 0)
    		execv(path, &args[1]);
		waitpid(-1, NULL, 0);
	}
	else if (i == 5)
	{
		if ((pid = fork()) == 0)
    		execv("/bin/ls", args);
		waitpid(-1, NULL, 0);
	}
}

int	cmdhandler(char *input)
{
	if (!ft_strncmp(input, "pwd", 3))
		check_pwd();
	else if (!ft_strncmp(input, "cd ", 3))
		do_cd(input);
	else if (!ft_strncmp(input, "cd", 2))
	{
		chdir("/nfs/homes/");
		printf("OI!\n");
	}
	else if (!ft_strncmp(input, "exit", 4))
		return (0);
	else if (!ft_strncmp(input, "clear", 5))
		clearcmd();
	else if (!ft_strncmp(input, "ls ", 2))
		lscmd(input);
	else
		printf("command not found: %s\n", input);
	return(1);
}
