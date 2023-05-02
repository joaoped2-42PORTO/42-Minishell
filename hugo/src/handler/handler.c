/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/05/02 15:34:15 by huolivei         ###   ########.fr       */
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

int	do_builtins(t_shell *args)
{
	int	pid;
	char	*path;
	char	*res;

	path = "/usr/bin/";
	res = ft_strjoin(path, args->split[0]);
	if ((pid = fork()) == 0)
	{
    	if(execv(res, args->split) != 0)
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

void	change_env_pwd(t_shell *args)
{
	int	i;
	char	path[1000];
	char	*str;

	str = "PWD=";
	i = -1;
	getcwd(path, sizeof(path));
	while (args->env[++i])
	{
		if (!ft_strcmp(args->env[i], "PWD"))
		{
			str = ft_strjoin(str, path);
			args->env[i] = ft_strdup(str);
			break;
		}
	}
	free(str);
}

void	change_env_oldpwd(t_shell *args)
{
	int	i;
	char	path[1000];
	char	*str;

	str = "OLDPWD=";
	i = -1;
	getcwd(path, sizeof(path));
	while (args->env[++i])
	{
		if (!ft_strcmp(args->env[i], "OLDPWD"))
		{
			str = ft_strjoin(str, path);
			args->env[i] = ft_strdup(str);
			break;
		}
	}
	free(str);
}

int	see_env_size(t_shell *args)
{
	int	i;

	i = 0;
		if (args->new_env[0] == 0)
	{
		while (args->env[i])
			i++;
		args->env[i] = malloc(sizeof(char) * ft_strlen(args->input));
	}
	else
	{
		while (args->new_env[i])
			i++;
		args->new_env[i] = malloc(sizeof(char) * ft_strlen(args->input));
	}
	return (i);
}

void	do_export(t_shell *args)
{
	int	i;
	int	j;
	int	x;

	x = 0;
	j = 7;
	if (args->split[2] != 0)
	{
		do_mult_export(args);
		return ;
	}
	if (args->split[1] == 0)
	{
		print_env(args);
		return ;
	}
	i = see_env_size(args);
	while(args->input[j])
	{
		if (args->input[j] == '"')
			j++;
		if (args->new_env[0] != 0)
			args->new_env[i][x++] = args->input[j++];
		else
			args->env[i][x++] = args->input[j++];
	}
	args->env[i][x] = '\0';
	i++;
	args->env[i] = 0;
}

void	do_unset(t_shell *args)
{
	int	i;
	int	j;
	int	x;

	x = 0;
	j = 0;
	i = 0;
	//args->new_env = malloc(sizeof(char *) * 256);
	while(args->split[i++])
	{
		if (args->split[i] == 0)
			break ;
		j = 0;
		while (args->env[j])
		{
			if (ft_strncmp(args->env[j], args->split[i], ft_strlen(args->split[i])))
			{
				args->new_env[x++] = ft_strdup(args->env[j]);
			}
			else if (!ft_strncmp(args->env[j], args->split[i], ft_strlen(args->split[i])))
			{
				args->env[j] = 0;
			}
			j++;
		}
	}
	args->new_env[x] = 0;
}

void	mult_export_new(t_shell *args)
{
	int	i;
	int	j;
	int	x;
	int	flag;
	int	y;

	y = 6;
	flag = 0;
	x = 0;
	j = 0;
	i = 0;
	while (args->input[y++])
	{
		if (args->input[y] == '"')
		{
			flag++;
			y++;
		}
		if (args->input[y] == '\0')
			break ;
		if (flag % 2 == 0 && flag != 0)
		{
			args->new_env[i][x] = '\0';
			i++;
			y++;
			if (args->input[y] != '\0')
				args->new_env[i] = malloc(sizeof(char) * (ft_strlen(args->input) - y));
			x = 0;
			flag = 0;
		}
		args->new_env[i][x] = args->input[y];
		x++;
	}
	args->new_env[i] = 0;
}


void	do_mult_export(t_shell *args)
{
	int	i;
	int	j;
	int	x;
	int	flag;
	int	y;

	y = 6;
	flag = 0;
	x = 0;
	j = 0;
	i = see_env_size(args);
	if (args->new_env[0] != 0)
	{
		mult_export_new(args);
		return ;
	}
	while (args->input[y++])
	{
		if (args->input[y] == '"')
		{
			flag++;
			y++;
		}
		if (args->input[y] == '\0')
			break ;
		if (flag % 2 == 0 && flag != 0)
		{
			args->env[i][x] = '\0';
			i++;
			y++;
			if (args->input[y] != '\0')
				args->env[i] = malloc(sizeof(char) * (ft_strlen(args->input) - y));
			x = 0;
			flag = 0;
		}
		else
		{
			args->env[i][x] = args->input[y];
			x++;
		}
	}
	args->env[i] = 0;
}

int	cmdhandler(t_shell *args)
{
	if (args->input[0] == '\0')
		return (1);
	else if (!ft_strncmp(args->split[0], "pwd", 3))
		check_pwd();
	else if (!ft_strncmp(args->split[0], "cd", 2))
		do_cd(args);
	else if (!ft_strncmp(args->split[0], "env", 3))
		print_env(args);
	else if (!ft_strncmp(args->split[0], "exit", 4))
		return (0);
	else if(!ft_strncmp(args->split[0], "echo", 4))
		do_echo(args);
	else if(!ft_strncmp(args->split[0], "export", 6))
		do_export(args);
	else if(!ft_strncmp(args->split[0], "unset", 5))
		do_unset(args);
	else if (do_builtins(args) == 1)
		return(1);
	return(1);
}
