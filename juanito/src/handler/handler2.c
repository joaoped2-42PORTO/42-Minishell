/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:28:17 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/15 12:14:43 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_non_builtins(t_shell *args)
{
	int		pid;
	char	*path;

	path = getthepath(args);
	pid = fork();
	if (pid == 0)
	{
		executepid(args);
		if (execve(path, args->split, args->env) != 0)
		{
			printf("command not found: %s\n", args->token->cmd);
			args->exit_status = 2;
			exit (2);
		}
		free(path);
		args->exit_status = 125;
	}
	waitpid(-1, NULL, 0);
	free(path);
	return (1);
}

void	print_env(t_shell *args)
{
	int	i;

	i = 0;
	while (args->env[i])
		printf("%s\n", args->env[i++]);
	args->exit_status = 0;
}

void	print_export(t_shell *args)
{
	int	i;
	int	j;

	i = 0;
	while (args->exp[i])
	{
		j = 0;
		printf("declare -x ");
		while (args->exp[i][j] != '=' && args->exp[i][j] != '\0')
			printf("%c", args->exp[i][j++]);
		if (args->exp[i][j])
		{
			printf("%c\"", args->exp[i][j++]);
			while (args->exp[i][j])
				printf("%c", args->exp[i][j++]);
			printf("\"");
		}
		printf("\n");
		i++;
	}
	args->exit_status = 0;
}

int	cmdhandler(t_shell *args)
{
	if (args->input[0] == '\0')
		return (1);
	else if (!ft_strncmp(args->token->cmd, "pwd", 3))
		check_pwd(args);
	else if (!ft_strncmp(args->token->cmd, "cd", 2))
		do_cd(args);
	else if (!ft_strncmp(args->token->cmd, "env", 3))
		print_env(args);
	else if (!ft_strncmp(args->token->cmd, "exit", 4))
		do_exit(args);
	else if (!ft_strncmp(args->token->cmd, "echo", 4))
		do_echo(args);
	else if (!ft_strncmp(args->token->cmd, "export", 6))
		do_export(args);
	else if (!ft_strncmp(args->token->cmd, "unset", 5))
		do_unset(args);
	else if (!ft_strncmp(args->input, "$?", 2))
		printf("%d\n", args->exit_status);
	else if (do_non_builtins(args) == 1)
		return (1);
	return (1);
}
