/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/27 23:26:30 by huolivei         ###   ########.fr       */
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

char	*get_acess(char	**str, t_comand *args)
{
	int i;
	char	*join;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		tmp = ft_strjoin(str[i], "/");
		join = ft_strjoin(tmp, args->cmd);
		free (tmp);
		if (access(join, F_OK) == 0)
			break;
		if (str[i + 1] == 0)
			break;
		i++;
		free (join);
	}
	free_matrix(str);
	return (join);
}

int	do_non_builtins(t_shell *args, t_comand *tmp)
{
	char	*path;
	char	**path_split;
	int		pid;

	path = get_path(args);
	if (path)
	{
		path_split = ft_split(path, ':');
		free (path);
		path = get_acess(path_split, tmp);
	}
	else
		return (0);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (args->input[0] == '.' && args->input[1] == '/')
			open_exec(args);
		else if(args->input[0] == '/')
			open_exec_abs(args);
   		if(execve(path, tmp->argm, args->env) != 0)
		{
			printf("command not found: %s\n", tmp->cmd);
			args->exit_status = 2;
			exit (2);
		}
	}
	wait(NULL);
	args->exit_status = 125;
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

/* void	redirection(t_comand *tmp)
{
	int	x;

	x = 0;
	while(tmp->out_red[x])
	{
		tmp->out_fd = open(tmp->out_red[x], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (tmp->out_fd == -1)
			perror("open");
		if (!tmp->out_red[x + 1])
		{
			dup2(tmp->out_fd, STDOUT_FILENO);
			break;
		}
		close(tmp->out_fd);
		x++;
	}
	x = 0;
	while (tmp->in_red[x])
	{
		tmp->in_fd = open(tmp->in_red[x], O_RDONLY);
		if (tmp->in_fd == -1)
			perror("open");
		if (!tmp->in_red[x + 1])
		{
			dup2(tmp->in_fd, STDIN_FILENO);
			break;
		}
		close(tmp->in_fd);
		x++;
	}
	x = 0;
	while (tmp->app_red[x])
	{
		tmp->app_fd = open(tmp->app_red[x], O_APPEND | O_CREAT | O_RDWR, 0777);
		if (tmp->app_fd == -1)
			perror("open");
		if (!tmp->app_red[x + 1])
		{
			dup2(tmp->app_fd, STDOUT_FILENO);
			break;
		}
		close(tmp->app_fd);
		x++;
	}
} */

void	close_redirection(t_shell *args)
{
	if (args->token->out_fd != -1)
	{
		dup2(args->old_out, STDOUT_FILENO);
		close(args->old_out);
		close(args->token->out_fd);
	}
	if (args->token->in_fd != -1)
	{
		dup2(args->old_in, STDIN_FILENO);
		close(args->old_in);
		close(args->token->in_fd);
	}
}

int	str_is_equal(char *str, char *str1)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (str1[j])
		j++;
	if (!ft_strncmp(str, str1, i) && i == j)
		return (1);
	return (0);
}

void	handle_input(t_shell *args, int *i)
{
	(*i)++;
	if (args->token->in_fd != -1)
		close (args->token->out_fd);
	args->token->in_fd = open(args->token->redir[*i], O_RDONLY, 0777);
	if (args->token->in_fd == -1)
		perror("open");
	dup2(args->token->in_fd, STDIN_FILENO);
}

void	handle_output(t_shell *args, int *i)
{
	(*i)++;
	if (args->token->out_fd != -1)
		close (args->token->out_fd);
	args->token->out_fd = open(args->token->redir[*i], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (args->token->out_fd == -1)
		perror("open");
	dup2(args->token->out_fd, STDOUT_FILENO);
}

void	handle_append(t_shell *args, int *i)
{
	(*i)++;
	if (args->token->out_fd != -1)
		close (args->token->out_fd);
	args->token->out_fd = open(args->token->redir[*i], O_APPEND | O_CREAT | O_RDWR, 0777);
	if (args->token->out_fd == -1)
		perror("open");
	dup2(args->token->out_fd, STDOUT_FILENO);
}


void	handle_redir(t_shell *args)
{
	int	i;

	i = 0;
	while (args->token->redir[i])
	{
		if (args->token->redir[i][0] == '>' && args->token->redir[i][1] == '>')
			handle_append(args, &i);
		/* else if ((args->token->redir[i][0] == '<' && args->token->redir[i][1] == '<'))
			handle_heredoc(args, &i); */
		else if (args->token->redir[i][0] == '>')
			handle_output(args, &i);
		else if (args->token->redir[i][0] == '<')
			handle_input(args, &i);
		i++;
	}
}
void	cmdhandler(t_shell *args)
{
	t_comand *tmp;

	tmp = args->token;
	args->old_out = dup(STDOUT_FILENO);
	args->old_in = dup(STDIN_FILENO);
	handle_redir(args);
	if (str_is_equal(tmp->cmd, "pwd"))
		check_pwd(args);
	else if (str_is_equal(tmp->cmd, "cd"))
		do_cd(args);
	else if (str_is_equal(tmp->cmd, "env"))
		print_env(args);
	else if (str_is_equal(tmp->cmd, "exit"))
		exit(args->exit_status);
	else if(str_is_equal(tmp->cmd, "echo"))
		do_echo(args);
	else if(str_is_equal(tmp->cmd, "export"))
		do_export(args);
	else if(str_is_equal(tmp->cmd, "unset"))
		do_unset(args);
	else if (str_is_equal(tmp->cmd, "$?"))
		printf("%d\n", args->exit_status);
	else
		do_non_builtins(args, tmp);
	close_redirection(args);
}

int	ft_size(t_comand *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		++i;
	}
	return (i);
}

void	executer(t_shell *args)
{
	int	size;

	size = ft_size(args->token);
	if (size == 1)
		cmdhandler(args);
	/* else
		mult_handler(args); */
}
