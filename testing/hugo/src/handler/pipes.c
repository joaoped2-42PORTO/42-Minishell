/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 20:06:47 by user              #+#    #+#             */
/*   Updated: 2023/06/22 22:51:47 by user             ###   ########.fr       */
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
	while (curr != NULL)
	{
		i++;
		curr = curr->next;
	}
	if (i == 0)
		return (0);
	return (i);
}

void	stringtreattopipe(t_shell *args)
{
    int j = 0;
    int k = 0;
    while (args->split[args->pipindex][j] != '|')
       args->pipindex++;
	args->string = malloc((args->pipindex + 1) * sizeof(char *));
	if (args->string == NULL)
		return ;
    if (args->split[args->string_index][j] == '|')
    {
        args->string_index++;
    }
	while (args->split[args->string_index] != NULL && args->split[args->string_index][j] != '|')
	{
		args->string[k] = args->split[args->string_index];
		args->string_index++;
		k++;
	}
    args->string[k] = NULL;
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
        stringtreattopipe(args);
		if (k != 0)
			token = token->next;
		path = returncompletepath(token, args);
		if (k == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			pid = fork();
			if (pid == 0)
				execve(path, args->string, NULL);
		}
		else if (k != i - 1)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			pipe(fd);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			pid = fork();
			if (pid == 0)
				execve(path, args->string, NULL);
		}
		else if (k == i - 1)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			dup2(out, STDOUT_FILENO);
			close(out);
			pid = fork();
			if (pid == 0)
				execve(path, args->string, NULL);
			dup2(in, STDIN_FILENO);
			close(in);
		}
		free(path);
    	free(args->string);
		k++;
	}
	waitpid(-1, NULL, 0);
	return (1);
}
