/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neddy <neddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:43:14 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/08 23:39:23 by neddy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	doexit1(t_shell *args)
{
	long	i;

	i = 0;
	if (str_is_equal(args->token->cmd, "exit"))
	{
		if (args->token->argm[1][0] == 45 || args->token->argm[1][0] == 43)
			i++;
		while (((args->token->argm[1][i] >= 48 && args->token->argm[1][i] <= 57)))
			i++;
		if (args->token->argm[1][i])
		{
			ft_putendl_fd("numeric argument required", 2);
			return (1);
		}
		if (ft_atoi(args->token->argm[1]) > LONG_MAX)
		{
			g_status = 2;
			printf("%s: %s: numeric argument required\n", args->token->cmd,
				args->token->argm[1]);
			exit(g_status);
		}
		if (args->token->argm[2])
		{
			printf("%s: too many arguments\n", args->token->cmd);
			g_status = 1;
			return (1);
		}
		else
			exit(ft_atoi(args->token->argm[1]));
	}
	return (0);
}

int	suppisbuiltin2(t_comand *tmp, t_shell *args)
{
	if (str_is_equal(args->token->cmd, "export"))
	{
		if (handleexporttopipe(tmp, args) == 1)
			return (1);
		g_status = 0;
		return (1);
	}
	else if (str_is_equal(args->token->cmd, "unset"))
	{
		g_status = 0;
		return (1);
	}
	return (0);
}

void	forknbt(t_shell *args, t_comand *token, int *fd)
{
	char	*path;
	int		pid;
	int		res;

	res = 0;
	path = returncompletepath(token, args);
	res = isbuiltin(token, args);
	if (res == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			close(fd[0]);
			do_non_builtinsforpipes(args, path);
		}
		signal(SIGINT, new_prompt);
	}
	free(path);
}

void	pipesloop(t_comand *token, t_shell *args, int *fd)
{
	t_comand	*ptr;
	int			k;

	k = 0;
	while (k < args->list_size)
	{
		if (k != 0)
		{
			args->flag = 0;
			ptr = token->next;
			free(token->cmd);
			free_matrix(token->argm);
			free_matrix(token->redir);
			free(token);
			token = ptr;
			args->token = token;
		}
		execpipes(token, args, fd, &k);
		k++;
	}
}
