/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/03 16:58:13 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*nonbuiltinspath(t_shell *args, t_comand *tmp, char *path)
{
	char	**path_split;

	path = get_path(args);
	if (path)
	{
		path_split = ft_split(path, ':');
		free(path);
		path = get_acess(path_split, tmp);
	}
	else
		return (0);
	return (path);
}

int	do_non_builtins(t_shell *args, t_comand *tmp)
{
	char	*path;
	int		pid;

	path = NULL;
	path = nonbuiltinspath(args, tmp, path);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (args->input[0] == '.' && args->input[1] == '/')
			open_exec(args);
		else if (args->input[0] == '/')
			open_exec_abs(args);
		if (execve(path, tmp->argm, args->env) != 0)
		{
			printf("command not found: %s\n", tmp->cmd);
			args->exit_status = 2;
			exit(2);
		}
	}
	wait(NULL);
	args->exit_status = 125;
	free(path);
	return (1);
}

void	cmdhandler(t_shell *args)
{
	t_comand	*tmp;

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
	else if (str_is_equal(tmp->cmd, "echo"))
		do_echo(args);
	else if (str_is_equal(tmp->cmd, "export"))
		do_export(args);
	else if (str_is_equal(tmp->cmd, "unset"))
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
	t_comand	*tmp;
	int			size;

	tmp = args->token;
	size = ft_size(tmp);
	if (size == 1)
		cmdhandler(args);
	else
		pipes(tmp, args);
}
