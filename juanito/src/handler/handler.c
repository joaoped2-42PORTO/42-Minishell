/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neddy <neddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/24 15:18:12 by neddy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char	*testingfc()
{
    char *path = getenv("PATH");
    char *dir = strtok(path, ":");
    char ls_path[256];
	char *dest;

    while (dir != NULL) {
        sprintf(ls_path, "%s/ls", dir);
        if (access(ls_path, X_OK) == 0)
            break;
        dir = strtok(NULL, ":");
    }

	dest = ft_strdup(ls_path);

	return (dest);
}

void	clearcmd()
{
	int pid;
	char *args[] = {"clear", NULL};

	if ((pid = fork()) == 0)
		execv("/usr/bin/clear", args);
	waitpid(-1, NULL, 0);
}

char *getarg(char *input)
{
	char *dest;

	dest = ft_strrchr(input, ' ');
	if (dest == NULL)
		dest = input;
	else
		dest++;
	return (dest);
}

void	lscmd(char *input)
{
	int pid;
	//char *dest = getarg(input);
	char *av[] = {"ls", NULL};
	char **tmp = "teste";
	int i = 0;

	while (tmp[1][i])
		write(1, &tmp[1][i++], 1);
	if ((pid = fork()) == 0)
		execv("/bin/ls", av);
	waitpid(-1, NULL, 0);
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
	else if (!ft_strcmp(input, " ls ") || !ft_strcmp(input, "ls"))
		lscmd(input);
	else
		printf("command not found: %s\n", input);
	return(1);
}
