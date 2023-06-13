/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:05:06 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/08 12:31:29 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_loop_doubles(t_shell *args, int j)
{
	int	i;

	i = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->split[j], args->env[i], variable_size(args->env[i])))
					return (0);
		i++;
	}
	return (1);
}

int	check_doubles_vars(t_shell *args)
{
	int	j;

	j = 0;
	while (args->split[j])
	{
		if(!do_loop_doubles(args, j))
			return (0);
		j++;
	}
	return (1);
}

int	see_env_size(t_shell *args)
{
	int	i;

	i = 0;
	while (args->env[i])
		i++;
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

int	see_split_size(t_shell *args)
{
	int	i;

	i = 0;
	while (args->split[i])
		i++;
	return (i);
}

void	exchange_memo(t_shell *args, char **env, char **exp, int *i, int *x)
{
	env = dup_env(args->env, env);
	exp = dup_env(args->exp, exp);
	free_matrix(args->env);
	free_matrix(args->exp);
	args->env = ft_calloc(*i + see_split_size(args), sizeof(char *));
	args->env = dup_env(env, args->env);
	//args->env[*i] = ft_calloc(ft_strlen(args->input), sizeof(char));
	args->exp = ft_calloc(*x + see_split_size(args), sizeof(char *));
	args->exp = dup_env(exp, args->exp);
	//args->exp[*i] = ft_calloc(ft_strlen(args->input), sizeof(char));
}
// Antigo single export
/*void	single_export(t_shell *args, int *j, int *x, int *i)
{
	char	**str;

	str = ft_calloc(*i + 1, sizeof(char *));
	exchange_memo(args, str, i);
	while (args->input[*j])
	{
		if (args->input[*j] == '"')
			(*j)++;
		if (args->input[*j] == '\0')
			break ;
		if (args->input[*j] == '$')
		{
			(*j)++;
			put_var_args(args, j, x, i);
		}
		else
			args->env[*i][(*x)++] = args->input[(*j)++];
		if (args->input[*j] == '\0')
			break ;
	}
	args->env[*i][*x] = '\0';
	free_matrix(str);
}*/
