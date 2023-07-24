/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:34:24 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/24 23:59:51 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (args->token->argm[0][0] == '.' || args->token->argm[0][0] == '/')
			open_exec(args, path);
		execthenonbuiltin(args, path);
	}
	signal(SIGINT, new_prompt);
	waitpid(pid, &g_status, 0);
	if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
	config_signals();
	free(path);
	return (1);
}

void	cmdhandler(t_shell *args)
{
	handler_init(args);
	if (!handle_redir(args))
		return ;
	if (args->token->cmd[0] == '\0')
	{
		close_redirection(args);
		return ;
	}
	if (str_is_equal(args->token->cmd, "pwd"))
		check_pwd(args);
	else if (str_is_equal(args->token->cmd, "cd"))
		do_cd(args);
	else if (str_is_equal(args->token->cmd, "env"))
	{
		if (args->token->argm[1])
		{
			args_in_exp();
			return ;
		}
		print_env(args);
	}
	else if (cmdhandler2(args) == 0)
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
