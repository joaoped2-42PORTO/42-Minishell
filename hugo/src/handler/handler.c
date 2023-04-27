/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/27 23:01:25 by huolivei         ###   ########.fr       */
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

void	do_builtins(t_shell *args)
{
	int	pid;
	char	*path;
	char	*res;

	path = "/bin/";
	res = ft_strjoin(path, args->split[0]);
	if ((pid = fork()) == 0)
	{
    		if(execv(res, args->split) != 0)
			{
				perror("Error");
				return ;
			}
	}
	waitpid(-1, NULL, 0);
	free(res);
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
		i = 8;
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

void	do_export(t_shell *args)
{
	int	i;
	int	j;
	int	x;

	x = 0;
	j = 7;
	i = 0;
	while (args->env[i])
		i++;
	args->env[i] = malloc(sizeof(char) * ft_strlen(args->input));
	while(args->input[j])
		args->env[i][x++] = args->input[j++];
	args->env[i][x] = '\0';
	i++;
	args->env[i] = 0;
}


int	cmdhandler(t_shell *args)
{
	if (!ft_strncmp(args->split[0], "pwd", 3))
		do_builtins(args);
	else if (!ft_strncmp(args->split[0], "cd", 2))
		do_cd(args);
	else if (!ft_strncmp(args->split[0], "env", 3))
		print_env(args);
	else if (!ft_strncmp(args->split[0], "exit", 4))
		return (0);
	else if (!ft_strncmp(args->split[0], "clear", 5))
		do_builtins(args);
	else if (!ft_strncmp(args->split[0], "ls ", 2))
		do_builtins(args);
	else if(!ft_strncmp(args->split[0], "echo", 4))
		do_echo(args);
	else if(!ft_strncmp(args->split[0], "export", 6))
		do_export(args);
	else
		printf("command not found: %s\n", args->input);
	return(1);
}
