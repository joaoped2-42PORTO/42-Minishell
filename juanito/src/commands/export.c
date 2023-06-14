/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:38:03 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/14 17:12:57 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_input_exp(t_shell *args)
{
	int	i;

	i = 0;
	while (args->input[i])
	{
		if (args->input[i] == '=' && args->input[i + 1] == ' ')
			return (0);
		i++;
	}
	return (1);
}

void	do_export(t_shell *args)
{

	if (args->split[1] == 0)
	{
		print_export(args);
		args->exit_status = 0;
		return ;
	}
	do_mult_export(args);
	args->exit_status = 0;
}

int	check_space_in_string(t_shell *args, int *y)
{
	int	j;

	j = *y;
	while (args->input[++j])
	{
		if (args->input[j] == '\"' || args->input[j] == '\'')
			return (1);
	}
	return (0);
}



int	ft_isalnum_mini(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	check_env_value(t_shell *args, char *str)
{
	int	i;

	i = 0;
	while (args->env[i])
	{
		if (!ft_strncmp(args->env[i], str, variable_size(args->env[i])))
			return (i);
		i++;
	}
	return (0);
}

int	see_if_env(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	see_exp_size(t_shell *args)
{
	int	i;

	i = 0;
	while (args->exp[i])
		i++;
	return (i);
}

void	do_mult_export(t_shell *args)
{
	int	i;
	int	x;
	int	y;
	char	**env;
	char	**exp;

	y = 0;
	args->flag = 0;
	x = see_exp_size(args);
	i = see_env_size(args);
	env = ft_calloc(i + 1, sizeof(char *));
	exp = ft_calloc(x + 1, sizeof(char *));
	exchange_memo(args, env, exp, &i, &x);
	while (args->split[++y])
	{
		if(!see_if_env(args->split[y]))
			args->exp[x++] = ft_strdup(args->split[y]);
		else
		{
			args->env[i++] = ft_strdup(args->split[y]);
			args->exp[x++] = ft_strdup(args->split[y]);
		}
	}
	free_matrix(env);
	free_matrix(exp);
	args->env[i] = 0;
	args->exp[x] = 0;
}
