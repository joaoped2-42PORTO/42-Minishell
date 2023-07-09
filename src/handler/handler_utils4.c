/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:01:43 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/09 17:20:25 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_heredoc(t_shell *args, int *i)
{
	(*i)++;
	start_heredoc(args, *i);
	args->token->in_fd = open("heredoc", O_RDONLY);
	if (args->token->in_fd == -1)
		perror("open");
	dup2(args->token->in_fd, STDIN_FILENO);
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

int	doexit(t_shell *args)
{
	long	i;

	i = 0;
	if (str_is_equal(args->token->cmd, "exit"))
	{
		if (args->token->argm[1][0] == 45 || args->token->argm[1][0] == 43)
			i++;
		while (((args->token->argm[1][i] >= 48
				&& args->token->argm[1][i] <= 57)))
			i++;
		if (ft_atoi(args->token->argm[1]) > LONG_MAX)
			nr_higher(args);
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

int	cmdhandler2(t_shell *args)
{
	if (doexit(args) == 1)
		return (1);
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
		return (0);
	return (1);
}
