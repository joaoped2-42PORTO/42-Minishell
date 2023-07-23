/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:25:28 by joaoped2          #+#    #+#             */
/*   Updated: 2023/07/23 15:00:53 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_exec_helper(t_shell *args, char *str, char *str1)
{
	(void)str;
	if (access(args->token->argm[0], X_OK) == 0)
		execve(args->token->argm[0], args->token->argm, NULL);
	else if (access(str, F_OK) == 0)
	{
		replace_stds(args);
		printf("%s: Permission denied\n", args->token->cmd);
		g_status = 126;
	}
	else if (execve(str, args->token->argm, NULL) != 0)
	{
		replace_stds(args);
		printf("%s: No such file or directory\n", args->token->cmd);
		free(str);
		g_status = 127;
		exit(g_status);
	}
	free(str1);
	free(str);
	free_split(args);
	free_list(args);
	do_small_exit(args);
	exit(g_status);
}

void	open_exec(t_shell *args, char *str1)
{
	char	*str;
	int		i;
	int		total;
	int		j;

	j = 0;
	total = (ft_strlen(args->pwd) + ft_strlen(args->split[0]));
	i = 4;
	str = malloc(total * sizeof(char));
	if (!str)
		return ;
	while (args->pwd[i])
		str[j++] = args->pwd[i++];
	i = 1;
	while (args->split[0][i])
		str[j++] = args->split[0][i++];
	str[j] = '\0';
	open_exec_helper(args, str, str1);
	free(str);
	g_status = 0;
	exit(g_status);
}

char	*get_path(t_shell *args)
{
	int		i;
	char	*str;

	i = 0;
	while (args->env[i])
	{
		if (var_is_equal(args->env[i], "PATH"))
		{
			str = ft_strdup(args->env[i]);
			return (str);
		}
		i++;
	}
	return (NULL);
}

char	*index_helper(char *tmp, int i, t_comand *args, char **str)
{
	char	*join;

	if (i == 0)
	{
		tmp = ft_strjoin(&str[i][5], "/");
		join = ft_strjoin(tmp, args->cmd);
		free(tmp);
	}
	else
	{
		tmp = ft_strjoin(str[i], "/");
		join = ft_strjoin(tmp, args->cmd);
		free(tmp);
	}
	return (join);
}

char	*get_acess(char **str, t_comand *args)
{
	int		i;
	char	*join;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		join = index_helper(tmp, i, args, str);
		if (access(join, F_OK) == 0)
			break ;
		if (str[i + 1] == 0)
			break ;
		i++;
		free(join);
	}
	free_matrix(str);
	return (join);
}
