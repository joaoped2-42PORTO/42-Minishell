/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:11:32 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/07 15:46:54 by joaoped2         ###   ########.fr       */
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
	suppisbuiltin(args);
	suppisbuiltin2(tmp, args);
	if (tmp->cmd[0] == '\0')
		return (1);
	if (str_is_equal(args->token->cmd, "pwd"))
		check_pwd(args);
	else if (str_is_equal(args->token->cmd, "cd"))
		do_cd(args);
	else if (str_is_equal(args->token->cmd, "env"))
		print_env(args);
	else if (str_is_equal(args->token->cmd, "echo"))
	{
		do_echo(args);
		g_status = 0;
	}
	else if (str_is_equal(args->token->cmd, "$?"))
		printf("%d\n", g_status);
	else
		return (0);
	return (1);
}

void	do_non_builtinsforpipes(t_shell *args, char *path)
{
	if (args->input[0] == '.' && args->input[1] == '/')
		open_exec(args);
	else if (args->input[0] == '/')
		open_exec_abs(args);
	execthenonbuiltin(args, path);
}
