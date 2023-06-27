/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:06:47 by user              #+#    #+#             */
/*   Updated: 2023/06/27 15:31:23 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*returncompletepath(t_comand *token, t_shell *args)
{
	char	*path;
	char	**path_split;

	path = get_path(args);
	if (path)
	{
		path_split = ft_split(path, ':');
		free(path);
		path = get_acess(path_split, token);
	}
	else
		return (0);
	return (path);
}

int	checklistsizeforpipes(t_comand *token)
{
	t_comand	*curr;
	int			i;

	i = 0;
	curr = token;
	while (curr)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}

int	isbuiltin(t_comand *tmp, t_shell *args)
{
	if (!ft_strncmp(tmp->cmd, "pwd", 3))
		check_pwd(args);
	else if (!ft_strncmp(tmp->cmd, "cd", 2))
		do_cd(args);
	else if (!ft_strncmp(tmp->cmd, "env", 3))
		print_env(args);
	else if (!ft_strncmp(tmp->cmd, "exit", 4))
		do_exit(args);
	else if (!ft_strncmp(tmp->cmd, "echo", 4))
		do_echo(args);
	else if (!ft_strncmp(tmp->cmd, "export", 6))
		return (1);
	else if (!ft_strncmp(tmp->cmd, "unset", 5))
		return (1);
	else if (!ft_strncmp(args->input, "$?", 2))
		printf("%d\n", args->exit_status);
	else
		return (0);
	return (1);
}

void	handlefirstpipe(t_comand *token, t_shell *args, int *fd)
{
	int		pid;
	char	*path;

	path = returncompletepath(token, args);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (isbuiltin(token, args) == 0)
	{
		pid = fork();
		if (pid == 0)
			execve(path, token->argm, NULL);
		waitpid(-1, NULL, 0);
	}
	free(path);
}

void	handlemidpipes(t_comand *token, t_shell *args, int *fd)
{
	int		pid;
	char	*path;

	path = returncompletepath(token, args);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	pipe(fd);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (isbuiltin(token, args) == 0)
	{
		pid = fork();
		if (pid == 0)
			execve(path, token->argm, NULL);
		waitpid(-1, NULL, 0);
	}
	free(path);
}

void	handlelastpipes(t_comand *token, t_shell *args)
{
	int		pid;
	char	*path;

	path = returncompletepath(token, args);
	if (isbuiltin(token, args) == 0)
	{
		pid = fork();
		if (pid == 0)
			execve(path, token->argm, NULL);
		waitpid(-1, NULL, 0);
	}
	free(path);
}

void	gotonextlist(t_comand *token, t_shell *args)
{
	token = token->next;
	args->token = token;
}

void	all(t_comand *token, t_shell *args, int *fd)
{
	int	in;
	int	out;
	int	k;
	int	i;

	k = 0;
	i = checklistsizeforpipes(token);
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	if (k != 0)
	{
		token = token->next;
		args->token = token;
	}
	if (k == 0)
		handlefirstpipe(token, args, fd);
	else if (k != i - 1)
		handlemidpipes(token, args, fd);
	else if (k == i - 1)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		dup2(out, STDOUT_FILENO);
		close(out);
		handlelastpipes(token, args);
		dup2(in, STDIN_FILENO);
		close(in);
	}
}

void	pipes(t_comand *token, t_shell *args)
{
	int	k;
	int	i;
	int	fd[2];


	i = checklistsizeforpipes(token);
	k = 0;
	pipe(fd);
	while (k < i)
	{
		all(token, args, fd);
		k++;
	}
}
