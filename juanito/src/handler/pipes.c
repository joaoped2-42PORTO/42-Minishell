/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:06:47 by user              #+#    #+#             */
/*   Updated: 2023/06/26 12:18:13 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*returncompletepath(t_comand *coms, t_shell *args)
{
	char	*path;
	char	**path_split;

	path = get_path(args);
	if (path)
	{
		path_split = ft_split(path, ':');
		free(path);
		path = get_acess(path_split, coms);
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
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	if (i == 1)
		return (0);
	return (i);
}

int	isbuiltin(t_comand *tmp, t_shell *args)
{
	// int	pid;

	// pid = fork();
	// if (pid == 0)
	// {
		// signal(SIGINT, SIG_DFL);
		// signal(SIGQUIT, SIG_DFL);
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
			do_export(args);
		else if (!ft_strncmp(tmp->cmd, "unset", 5))
			do_unset(args);
		else if (!ft_strncmp(args->input, "$?", 2))
			printf("%d\n", args->exit_status);
		else
			return (0);
 	// }
	// while (waitpid(-1, NULL, 0) > 0)
	// 	continue ;
	return (1);
}

int	pipes(t_comand *token, t_shell *args)
{
	int		k;
	int		i;
	int		fd[2];
	int		pid;
	char	*path;
	int		in;
	int		out;

	i = 0;
	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	i = checklistsizeforpipes(token);
	k = 0;
	pipe(fd);
	while (k < i)
	{
		if (k != 0)
			token = token->next;
		path = returncompletepath(token, args);
		if (k == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			if (isbuiltin(token, args) == 0)
			{
				pid = fork();
				if (pid == 0)
					execve(path, token->argm, NULL);
				else
					waitpid(-1, NULL, 0);
			}
		}
		else if (k != i - 1)
		{
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
				else
					waitpid(-1, NULL, 0);
			}
		}
		else if (k == i - 1)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			dup2(out, STDOUT_FILENO);
			close(out);
			if (isbuiltin(token, args) == 0)
			{
				pid = fork();
				if (pid == 0)
					execve(path, token->argm, NULL);
				else
					waitpid(-1, NULL, 0);
			}
			dup2(in, STDIN_FILENO);
			close(in);
		}
		free(path);
		k++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		continue ;
	return (1);
}
