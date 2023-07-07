/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:01:43 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/07 17:58:54 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc(t_shell *args, int *i)
{
	(*i)++;
	if (args->token->in_fd != -1)
		close(args->token->out_fd);
	args->heredoc = 1;
	start_heredoc(args, i);
	args->token->in_fd = open("heredoc", O_RDONLY);
	if (args->token->in_fd == -1)
		perror("open");
	dup2(args->token->in_fd, STDIN_FILENO);
	args->heredoc = 0;
}

void	execthenonbuiltin(t_shell *args, char *path)
{
	if (execve(path, args->token->argm, args->env) != 0)
	{
		printf("command not found: %s\n", args->token->cmd);
		g_status = 127;
		free(path);
		free_split(args);
		free_list(args);
		do_small_exit(args);
	}
}

void	doexit(t_shell *args)
{
	int	i;
	int	x;

	x = 19;
	i = 0;
	if (str_is_equal(args->token->cmd, "exit"))
	{
		while ((args->token->argm[1][i] >= 48 && args->token->argm[1][i] <= 57))
			i++;
		if (args->token->argm[1][i] || i > x)
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
		}
		else
			exit(ft_atoi(args->token->argm[1]));
	}
	return ;
}

int	cmdhandler2(t_shell *args)
{
	doexit(args);
	if (str_is_equal(args->token->cmd, "echo"))
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
		return (0);
	return (1);
}
