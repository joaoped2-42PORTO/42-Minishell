/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:11:32 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/29 14:31:50 by joaoped2         ###   ########.fr       */
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

void	handleexporttopipe(t_comand *tmp, t_shell *args)
{
	if (tmp->argm[1] == 0)
		print_export(args);
	else
		return ;
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
