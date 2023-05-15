/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:38:03 by huolivei          #+#    #+#             */
/*   Updated: 2023/05/15 13:17:43 by huolivei         ###   ########.fr       */
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
	int	i;
	int	j;
	int	x;

	x = 0;
	j = 7;
	if (!check_doubles_vars(args))
	{
		args->exit_status = 0;
		return ;
	}
	if (args->split[1] == 0)
	{
		print_export(args);
		args->exit_status = 0;
		return ;
	}
	else if (args->split[2] != 0)
	{
		do_mult_export(args);
		args->exit_status = 0;
		return ;
	}
	i = see_env_size(args);
	single_export(args, &j, &x, &i);
	i++;
	args->env[i] = 0;
	args->exit_status = 0;
}

void	do_loop_new_export(t_shell *args, int *y, int *x, int *i)
{
	if (args->input[*y] == '"')
	{
		args->flag++;
		(*y)++;
	}
	if (args->flag % 2 == 0 && args->flag != 0)
	{
		args->new_env[*i][*x] = '\0';
		(*i)++;
		(*y)++;
		if (args->input[*y] != '\0')
			args->new_env[*i] = malloc(sizeof(char)
					* (ft_strlen(args->input) - *y));
		*x = 0;
		args->flag = 0;
	}
	else if (args->input[*y] != ' ')
		args->new_env[*i][(*x)++] = args->input[*y];
	if (args->flag == 0 && args->input[*y] == ' ')
	{
		(*i)++;
		args->new_env[*i] = malloc(sizeof(char)
				* (ft_strlen(args->input) - *y));
		*x = 0;
	}
}

void	mult_export_new(t_shell *args)
{
	int	i;
	int	x;
	int	y;

	y = 6;
	x = 0;
	i = 0;
	while (args->input[y++])
	{
		if (args->input[y] == '\0')
			break ;
		do_loop_new_export(args, &y, &x, &i);
		if ((args->input[y] == '=' && args->input[y + 1] == ' ') || (args->input[y] == '=' && args->input[y - 1] == ' '))
		{
			printf("Wrong identifier\n");
			args->exit_status = 1;
			break ;
		}
	}
	i++;
	args->new_env[i] = 0;
}

void	do_loop_export(t_shell *args, int *y, int *x, int *i)
{
	if (args->input[*y] == '"')
	{
		args->flag++;
		(*y)++;
	}
	if (args->flag % 2 == 0 && args->flag != 0)
	{
		args->env[*i][*x] = '\0';
		(*i)++;
		(*y)++;
		if (args->input[*y] != '\0')
			args->env[*i] = malloc(sizeof(char)
					* (ft_strlen(args->input) - *y));
		*x = 0;
		args->flag = 0;
	}
	else if (args->input[*y] != ' ')
		args->env[*i][(*x)++] = args->input[*y];
	if (args->flag == 0 && args->input[*y] == ' ')
	{
		args->env[*i][*x] = '\0';
		(*i)++;
		args->env[*i] = malloc(sizeof(char) * (ft_strlen(args->input) - *y));
		*x = 0;
	}
}

void	do_mult_export(t_shell *args)
{
	int	i;
	int	x;
	int	y;

	y = 6;
	args->flag = 0;
	x = 0;
	i = see_env_size(args);
	if (args->new_env[0] != 0)
	{
		mult_export_new(args);
		return ;
	}
	args->env[i] = malloc(ft_strlen(args->input) * sizeof(char));
	while (args->input[y++])
	{
		if (args->input[y] == '\0')
			break ;
		do_loop_export(args, &y, &x, &i);
		if ((args->input[y] == '=' && args->input[y + 1] == ' ') || (args->input[y] == '=' && args->input[y - 1] == ' '))
		{
			printf("Wrong identifier\n");
			args->exit_status = 1;
			break ;
		}
	}
	i++;
	args->env[i] = 0;
}
