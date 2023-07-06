/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:27:20 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/06 16:12:56 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_shell *args)
{
	int	i;

	i = 0;
	while (args->env[i])
		printf("%s\n", args->env[i++]);
	g_status = 0;
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
	g_status = 0;
}

void	open_exec_abs(t_shell *args)
{
	if (execve(args->split[0], args->split, NULL) != 0)
	{
		printf("%s: No such file or directory\n", args->token->cmd);
		g_status = 126;
		exit(g_status);
	}
	g_status = 0;
	exit(g_status);
}

# define HERE printf("Here\n")

void	close_redirection(t_shell *args)
{
	// printf("args->token->out_fd %d to command %s\n", args->token->out_fd, args->token->cmd);
	// printf("args->token->in_fd %d to command %s\n", args->token->in_fd, args->token->cmd);
	if (args->token->out_fd != -1)
	{
		//HERE;
		dup2(args->old_out, STDOUT_FILENO);
		//HERE;
		close(args->old_out);
		//HERE;
		close(args->token->out_fd);
		//HERE;
		// printf("Closing file fd: %d\n", args->token->out_fd);
	}
 	if (args->token->in_fd != -1)
	{
		dup2(args->old_in, STDIN_FILENO);
		close(args->old_in);
		close(args->token->in_fd);
	}
	unlink("heredoc");
}

int	str_is_equal(char *str, char *str1)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (str1[j])
		j++;
	if (!ft_strncmp(str, str1, i) && i == j)
		return (1);
	return (0);
}
