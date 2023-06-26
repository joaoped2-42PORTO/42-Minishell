/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:28:17 by joaoped2          #+#    #+#             */
/*   Updated: 2023/06/26 12:07:20 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_non_builtins(t_shell *args, t_comand *tmp)
{
	int		pid;
	char	*path;
	char	**path_split;

	path = get_path(args);
	if (path)
	{
		path_split = ft_split(path, ':');
		free (path);
		path = get_acess(path_split, tmp);
	}
	else
		return (0);
	if ((pid = fork()) == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (args->input[0] == '.' && args->input[1] == '/')
			open_exec(args);
		else if(args->input[0] == '/')
			open_exec_abs(args);
    	if(execve(path, tmp->argm, args->env) != 0)
		{
			printf("command not found: %s\n", tmp->cmd);
			args->exit_status = 2;
			exit (2);
		}
		args->exit_status = 125;
	}
	waitpid(-1, NULL, 0);
	free (path);
	return(1);
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
	t_comand *tmp;

	tmp = args->token;
	args->old_out = dup(STDOUT_FILENO);
	args->old_in = dup(STDIN_FILENO);
	if(checklistsizeforpipes(tmp) <= 1)
	{
		while (tmp)
		{
		//redirection(args, tmp);
		if (!ft_strncmp(tmp->cmd, "pwd", 3))
			check_pwd(args);
		else if (!ft_strncmp(tmp->cmd, "cd", 2))
			do_cd(args);
		else if (!ft_strncmp(tmp->cmd, "env", 3))
			print_env(args);
		else if (!ft_strncmp(tmp->cmd, "exit", 4))
			do_exit(args);
		else if(!ft_strncmp(tmp->cmd, "echo", 4))
			do_echo(args);
		else if(!ft_strncmp(tmp->cmd, "export", 6))
			do_export(args);
		else if(!ft_strncmp(tmp->cmd, "unset", 5))
			do_unset(args);
		else if (!ft_strncmp(args->input, "$?", 2))
			printf("%d\n", args->exit_status);
		//else
		//	do_non_builtins(args, tmp);
		//close_redirection(args);
		if (tmp != NULL)
			tmp = tmp->next;
		}
	}
	else
		pipes(tmp, args);
	return(1);
}
