/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:38:03 by huolivei          #+#    #+#             */
/*   Updated: 2023/06/11 18:42:46 by huolivei         ###   ########.fr       */
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

// Antigo export
	/*int	i;
	int	j;
	int	x;

	x = 0;
	j = 7;*/
	/*if (!check_doubles_vars(args))
		do_unset(args);*/
	/*else if (args->split[2] != 0)
	{
		do_mult_export(args);
		args->exit_status = 0;
		return ;
	}
	i = see_env_size(args);
	single_export(args, &j, &x, &i);
	i++;
	args->env[i] = 0;*/

//Antigo loop de export
	/*if (args->flag == 0 && args->input[*y] == ' ')
	{
		args->env[*i][*x] = '\0';
		(*i)++;
		args->env[*i] = ft_calloc(ft_strlen(args->input), sizeof(char *));
		*x = 0;
	}

	int	do_loop_export(t_shell *args, int *y, int *x, int *i)
{
	if (args->input[*y] == '=')
	{
		if (!check_space_in_string(args, y))
		{
			while (args->input[*y] != ' ' || !args->input[*y])
			{
				args->env[*i][(*x)++] = args->input[(*y)++];
			}
			return (0);
		}
	}
	if (args->input[*y] == '\"' || args->input[*y] == '\'')
	{
		args->flag++;
		(*y)++;
	}
	if (args->flag % 2 == 0 && args->flag != 0 && args->input[*y] == ' ')
	{
		args->env[*i][*x] = '\0';
		(*i)++;
		if (args->input[*y] != '\0')
		{
			//(*y)++;
			args->env[*i] = ft_calloc(ft_strlen(args->input), sizeof(char *));
		}
		if (args->input[*y] == '\0')
			return (1);
		*x = 0;
		args->flag = 0;
	}
	else if (args->input[*y] != '\0' && args->input[*y] != '\"' && args->input[*y] != '\'')
		args->env[*i][(*x)++] = args->input[*y];
	return (1);
}

void	put_var_args(t_shell *args, int *y, int *x, int *i)
{
	char	*str;
	int		j;
	int		k;
	int		t;
	int		index;
	char	*tmp;

	index = 0;
	j = 0;
	t = 0;
	str = ft_calloc(ft_strlen(args->input), sizeof(char));
	while (ft_isalnum_mini(args->input[*y]))
		str[j++] = args->input[(*y)++];
	if(str[0] == '\0')
	{
		free (str);
		return ;
	}
	k = check_env_value(args, str);
	if (k == 0)
		return;
	tmp = ft_calloc(ft_strlen(args->input) + ft_strlen(args->env[k]), sizeof(char));
	j = 0;
	while (args->env[*i][index])
		tmp[t++] = args->env[*i][index++];
	index = 0;
	free (args->env[*i]);
	args->env[*i] = ft_calloc(ft_strlen(args->input) + ft_strlen(args->env[k]), sizeof(char));
	t = 0;
	while (tmp[t])
		args->env[*i][index++] = tmp[t++];
	while (args->env[k][j] != '=')
		j++;
	j++;
	while (args->env[k][j])
		args->env[*i][(*x)++] = args->env[k][j++];
	free (str);
	free (tmp);

}

	*/

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
