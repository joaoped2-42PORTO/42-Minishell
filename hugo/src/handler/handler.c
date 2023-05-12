/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/12 15:23:34 by huolivei         ###   ########.fr       */
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

void	open_exec(t_shell *args)
{
	char	*str;
	int		i;
	int		total;
	int		j;

	j = 0;
	total = (ft_strlen(args->path) + ft_strlen(args->split[0]));
	i = 4;
	str = malloc(total * sizeof(char));
	if (!str)
		return ;
	while (args->path[i])
		str[j++] = args->path[i++];
	i = 1;
	while(args->split[0][i])
		str[j++] = args->split[0][i++];
	str[j] = '\0';
	if (execve(str, args->split, NULL) != 0)
	{
		perror("Error");
		exit (1);
	}
}

void	open_exec_abs(t_shell *args)
{
	if (execve(args->split[0], args->split, NULL) != 0)
	{
		perror("Error");
		exit (1);
	}
}

int	do_builtins(t_shell *args)
{
	int	pid;
	char	*path;
	char	*res;

	path = "/usr/bin/";
	res = ft_strjoin(path, args->split[0]);
	if ((pid = fork()) == 0)
	{
		child_signals();
		if (args->input[0] == '.' && args->input[1] == '/')
			open_exec(args);
		else if(args->input[0] == '/')
			open_exec_abs(args);
    	else if(execve(res, args->split, NULL) != 0)
		{
			printf("command not found: %s\n", args->input);
			exit (1);
		}
	}
	waitpid(-1, NULL, 0);
	free(res);
	return(1);
}

void	print_env(t_shell *args)
{
	int	i;

	i = 0;
	if (args->new_env[0] == 0)
	{
		while(args->env[i])
			printf("%s\n", args->env[i++]);
	}
	else
	{
		while(args->new_env[i])
			printf("%s\n", args->new_env[i++]);
	}
}

void	print_export(t_shell *args)
{
	int	i;

	i = 0;
	if (args->new_env[0] == 0)
	{
		while(args->env[i])
			printf("declare -x %s\n", args->env[i++]);
	}
	else
	{
		while(args->new_env[i])
			printf("declare -x %s\n", args->new_env[i++]);
	}
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

void	do_exit(t_shell *args)
{
	int	i;

	i = -1;
	while (args->split[++i])
		free(args->split[i]);
	free(args->split);
	i = -1;
	while (args->env[++i] != 0)
		free(args->env[i]);
	free(args->env);
	i = -1;
	while (args->new_env[++i] != 0)
		free(args->new_env[i]);
	free(args->new_env);
	free(args->path);
	free(args);
	rl_clear_history();
	exit (0);
}

void	do_small_exit(t_shell *args)
{
	int	i;

	i = -1;
	while (args->env[++i] != 0)
		free(args->env[i]);
	free(args->env);
	i = -1;
	while (args->new_env[++i] != 0)
		free(args->new_env[i]);
	free(args->new_env);
	free(args->path);
	free(args);
	rl_clear_history();
	exit (0);
}

int	cmdhandler(t_shell *args)
{
	if (args->input[0] == '\0')
		return (1);
	else if (!ft_strncmp(args->split[0], "pwd", 3))
		check_pwd(args);
	else if (!ft_strncmp(args->split[0], "cd", 2))
		do_cd(args);
	else if (!ft_strncmp(args->split[0], "env", 3))
		print_env(args);
	else if (!ft_strncmp(args->split[0], "exit", 4))
		do_exit(args);
	else if(!ft_strncmp(args->split[0], "echo", 4))
		do_echo(args);
	else if(!ft_strncmp(args->split[0], "export", 6))
		do_export(args);
	else if(!ft_strncmp(args->split[0], "unset", 5))
	{
		if (args->new_env[0] == 0)
			do_unset(args);
		else if (args->env[0] == 0)
			do_unset_new(args);
	}
	else if (do_builtins(args) == 1)
		return(1);
	return(1);
}
