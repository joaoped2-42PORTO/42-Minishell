/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:05:06 by huolivei          #+#    #+#             */
/*   Updated: 2023/05/17 22:34:40 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_loop_new_doubles(t_shell *args, int j)
{
	int	i;

	i = 0;
	while (args->new_env[i])
	{
		if (!ft_strncmp(args->split[j], args->new_env[i], variable_size(args->split[j])))
					return (0);
		i++;
	}
	return (1);
}

int	do_loop_doubles(t_shell *args, int j)
{
	int	i;

	i = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->split[j], args->env[i], variable_size(args->split[j])))
					return (0);
		i++;
	}
	return (1);
}

int	check_doubles_vars(t_shell *args)
{
	int	j;

	j = 0;
	if (args->new_env[0] == 0)
	{
		while (args->split[j])
		{
			if(!do_loop_doubles(args, j))
				return (0);
			j++;
		}
	}
	else
	{
		while (args->split[j])
		{
			if (!do_loop_new_doubles(args, j))
				return (0);
			j++;
		}
	}
	return (1);
}

int	see_env_size(t_shell *args)
{
	int	i;

	i = 0;
	if (args->new_env[0][0] == '1')
	{
		while (args->env[i])
			i++;
	}
	else
	{
		while (args->new_env[i])
			i++;
	}
	return (i);
}

char	**dup_env(char **str, char **str1)
{
	int	i;

	i = -1;
	while (str[++i])
		str1[i] = ft_strdup(str[i]);
	str1[i] = 0;
	return (str1);
}

void	free_matrix(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void	exchange_memo(t_shell *args, char **str, int *i)
{
	str = dup_env(args->env, str);
	free_matrix(args->env);
	args->env = ft_calloc(*i + 2, sizeof(char *));
	args->env = dup_env(str, args->env);
	args->env[*i] = ft_calloc(ft_strlen(args->input), sizeof(char));
}

void	exchange_memo_new(t_shell *args, char **str, int *i)
{
	str = dup_env(args->new_env, str);
	free_matrix(args->new_env);
	args->new_env = ft_calloc(*i + 2, sizeof(char *));
	args->new_env = dup_env(str, args->new_env);
	args->new_env[*i] = ft_calloc(ft_strlen(args->input), sizeof(char));
}

void	single_export(t_shell *args, int *j, int *x, int *i)
{
	char	**str;

	str = ft_calloc(*i + 1, sizeof(char *));
	if (args->env[0][0] != '1')
		exchange_memo(args, str, i);
	else
		exchange_memo_new(args, str, i);
	while (args->input[*j])
	{
		if (args->input[*j] == '"')
			(*j)++;
		if (args->new_env[0][0] != '1')
			args->new_env[*i][(*x)++] = args->input[(*j)++];
		else
			args->env[*i][(*x)++] = args->input[(*j)++];
	}
	if (args->new_env[0][0] != '1')
		args->new_env[*i][*x] = '\0';
	else
		args->env[*i][*x] = '\0';
	free_matrix(str);
}
