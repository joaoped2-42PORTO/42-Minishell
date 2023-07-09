/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:27:20 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/09 13:39:36 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	close_redirection(t_shell *args)
{
	if (args->token->out_fd != -1)
	{
		dup2(args->out, STDOUT_FILENO);
		close(args->out);
		close(args->token->out_fd);
	}
	if (args->token->in_fd != -1)
	{
		dup2(args->in, STDIN_FILENO);
		close(args->in);
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
