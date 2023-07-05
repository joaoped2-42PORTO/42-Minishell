/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/05 19:39:01 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*nonbuiltinspath(t_shell *args, char *path)
{
	char	**path_split;

	path = get_path(args);
	if (path)
	{
		path_split = ft_split(path, ':');
		free(path);
		path = get_acess(path_split, args->token);
	}
	else
		return (0);
	return (path);
}

int	do_non_builtins(t_shell *args)
{
	char	*path;
	int		pid;

	path = NULL;
	path = nonbuiltinspath(args, path);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (args->input[0] == '.' && args->input[1] == '/')
			open_exec(args);
		else if (args->input[0] == '/')
			open_exec_abs(args);
		execthenonbuiltin(args, path);
	}
	waitpid(pid, &g_status, 0);
	if (WIFEXITED(g_status))
            g_status = WEXITSTATUS(g_status);
	free(path);
	return (1);
}

void	cmdhandler(t_shell *args)
{
	args->old_out = dup(STDOUT_FILENO);
	args->old_in = dup(STDIN_FILENO);
	handle_redir(args);
	if (args->token->cmd[0] == '\0')
		return ;
	if (str_is_equal(args->token->cmd, "pwd"))
		check_pwd(args);
	else if (str_is_equal(args->token->cmd, "cd"))
		do_cd(args);
	else if (str_is_equal(args->token->cmd, "env"))
		print_env(args);
	else if (str_is_equal(args->token->cmd, "exit"))
		exit(g_status);
	else if (str_is_equal(args->token->cmd, "echo"))
	{
		do_echo(args);
		g_status = 0;
	}
	else if (str_is_equal(args->token->cmd, "export"))
		do_export(args);
	else if (str_is_equal(args->token->cmd, "unset"))
		do_unset(args);
	else if (str_is_equal(args->token->cmd, "$?"))
		printf("%d\n", g_status);
	else
		do_non_builtins(args);
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
	size = ft_size(args->token);
	if (size == 1)
		cmdhandler(args);
	else
		pipes(tmp, args);
}
