/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/13 16:00:08 by huolivei         ###   ########.fr       */
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

char	*print_env_var(t_shell *args, char *str)
{
	int		i;
	int		j;
	char	*src;

	i = 0;
	j = 0;
	src = NULL;
	while (args->env[i])
	{
		j = 0;
		while (args->env[i][j] && str[j] && args->env[i][j] == str[j])
			j++;
		if (args->env[i][j] == '=' && str[j] == '\0')
		{
			j++;
			free(src);
			src = ft_strdup(&args->env[i][j]);
			break ;
		}
		i++;
	}
	if (src == NULL)
		return (NULL);
	return (src);
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
		free (str);
		args->exit_status = 126;
		exit (126);
	}
	free (str);
	args->exit_status = 0;
	exit (0);
}

void	open_exec_abs(t_shell *args)
{
	if (execve(args->split[0], args->split, NULL) != 0)
	{
		perror("Error");
		args->exit_status = 126;
		exit (126);
	}
	args->exit_status = 0;
	exit (0);
}

char	*get_path(t_shell *args)
{
	int	i;
	char	*str;

	i = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->env[i], "PATH", 4))
		{
			str = ft_strdup(args->env[i]);
			return (str);
		}
		i++;
	}
	return (NULL);
}

char	*get_acess(char	**str, t_shell *args)
{
	int i;
	char	*join;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		tmp = ft_strjoin(str[i], "/");
		join = ft_strjoin(tmp, args->token->cmd);
		free (tmp);
		if (access(join, X_OK) == 0)
			break;
		if (str[i + 1] == 0)
			break;
		i++;
		free (join);
	}
	free_matrix(str);
	return (join);
}

int	do_non_builtins(t_shell *args)
{
	int	pid;
	char	*path;
	char	**path_split;

	path = get_path(args);
	if (path)
	{
		path_split = ft_split(path, ':');
		free (path);
		path = get_acess(path_split, args);
	}
	else
		return (0);
	if ((pid = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (args->input[0] == '.' && args->input[1] == '/')
			open_exec(args);
		else if(args->input[0] == '/')
			open_exec_abs(args);
    	if(execve(path, args->split, args->env) != 0)
		{
			printf("command not found: %s\n", args->token->cmd);
			args->exit_status = 2;
			exit (2);
		}
		args->exit_status = 125;
	}
	waitpid(-1, NULL, 0);
	free (path);
	return(1);
}

void	print_env(t_shell *args)
{
	int	i;

	i = 0;
	while(args->env[i])
		printf("%s\n", args->env[i++]);
	args->exit_status = 0;
}

void	print_export(t_shell *args)
{
	int	i;
	int	j;

	i = 0;
	while(args->exp[i])
	{
		j = 0;
		printf("declare -x ");
		while (args->exp[i][j] != '=' && args->exp[i][j] != '\0')
			printf("%c", args->exp[i][j++]);
		if (args->exp[i][j])
		{
			printf("%c\"", args->exp[i][j++]);
			while (args->exp[i][j])
				printf("%c", args->exp[i][j++]);
			printf("\"");
		}
		printf("\n");
		i++;
	}
	args->exit_status = 0;
}

int	cmdhandler(t_shell *args)
{
	if (args->input[0] == '\0')
		return (1);
	else if (!ft_strncmp(args->token->cmd, "pwd", 3))
		check_pwd(args);
	else if (!ft_strncmp(args->token->cmd, "cd", 2))
		do_cd(args);
	else if (!ft_strncmp(args->token->cmd, "env", 3))
		print_env(args);
	else if (!ft_strncmp(args->token->cmd, "exit", 4))
		do_exit(args);
	else if(!ft_strncmp(args->token->cmd, "echo", 4))
		do_echo(args);
	else if(!ft_strncmp(args->token->cmd, "export", 6))
		do_export(args);
	else if(!ft_strncmp(args->token->cmd, "unset", 5))
		do_unset(args);
	else if (!ft_strncmp(args->input, "$?", 2))
		printf("%d\n", args->exit_status);
	else if (do_non_builtins(args) == 1)
		return(1);
	return(1);
}
