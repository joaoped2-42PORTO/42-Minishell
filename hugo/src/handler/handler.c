/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/26 22:13:30 by huolivei         ###   ########.fr       */
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

int	ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (!s1 && !s2 && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	clearcmd(t_shell *args)
{
	int pid;

	if ((pid = fork()) == 0)
	{
    		if(execv("/bin/clear", args->split) != 0)
			{
				perror("Error:");
				return ;
			}
	}
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
				perror("Error:");
				return ;
			}
	}
	waitpid(-1, NULL, 0);
}

void	print_env(t_shell *args)
{
	int	i;

	i = 0;
	while(args->env[i])
		printf("%s\n", args->env[i++]);
}

void	do_echo(t_shell *args)
{
	int	i;

	if (!ft_strncmp(args->split[1], "-n", 2))
	{
		i = 7;
		while(args->input[i])
			write(1, &args->input[i++], 1);
	}
	else
	{
		i = 5;
		while(args->input[i])
			write(1, &args->input[i++], 1);
		write(1, "\n", 1);
	}
}

int	cmdhandler(t_shell *args)
{
	if (!ft_strncmp(args->split[0], "pwd", 3))
		check_pwd();
	else if (!ft_strncmp(args->split[0], "cd", 2))
		do_cd(args);
	else if (!ft_strncmp(args->split[0], "env", 3))
		print_env(args);
	else if (!ft_strncmp(args->split[0], "exit", 4))
		return (0);
	else if (!ft_strncmp(args->split[0], "clear", 5))
		clearcmd(args);
	else if (!ft_strncmp(args->split[0], "ls ", 2))
		lscmd(args);
	else if(!ft_strncmp(args->split[0], "echo", 4))
		do_echo(args);
	else
		printf("command not found: %s\n", args->input);
	return(1);
}
