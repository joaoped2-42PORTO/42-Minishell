/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:11:32 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/04 23:50:03 by huolivei         ###   ########.fr       */
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

int	handleexporttopipe(t_comand *tmp, t_shell *args)
{
	if (tmp->argm[1] == 0)
		print_export(args);
	else
		return (0);
	return (1);
}

int	isbuiltin(t_comand *tmp, t_shell *args)
{
	handle_redir(args);
	if (tmp->cmd[0] == '\0')
		return (1);
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
	{
		if (handleexporttopipe(tmp, args) == 1)
			return (1);
		return (1);
	}
	else if (!ft_strncmp(tmp->cmd, "unset", 5))
		return (1);
	else if (!ft_strncmp(args->input, "$?", 2))
		printf("%d\n", args->exit_status);
	else
		return (0);
	close_redirection(args);
	return (1);
}
