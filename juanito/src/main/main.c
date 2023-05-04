/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/05/04 14:47:18 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	morefunctions(t_shell *args, int x, int j, int flag)
{
	int	y;

	y = 0;
	while (args->split[x][j] != '"')
	{
		flag = 1;
		args->exp[y] = args->split[x][j];
		j++;
		y++;
		if (args->split[x][j] == '\0')
			break ;
	}
}

void	bigiumtrue(t_shell *args, int x, int j, int flag)
{
	int	y;

	y = 0;
	if (args->split[x][j] == '"')
	{
		j++;
		while (1)
		{
			if (args->split[x] == 0)
				break ;
			morefunctions(args, x, j, flag);
			if (flag == 1)
				args->exp[y++] = ' ';
			j = 0;
			x++;
		}
		flag = 1;
	}
}

void	check_valid_input(t_shell *args)
{
	int	j;
	int	x;
	int	flag;

	x = 0;
	j = 0;
	args->exp = ft_calloc(ft_strlen(args->input), sizeof(char));
	while (args->split[x])
	{
		j = 0;
		flag = 0;
		while (args->split[x][j])
		{
			bigiumtrue(args, x, j, flag);
			if (args->split[x] == 0)
				break ;
			j++;
		}
		if (args->split[x] == 0)
			break ;
		x++;
	}
	args->exp = ft_strtrim(args->exp, " ");
}

int	main(int ac, char **av, char **env)
{
	t_shell	*args;

	(void)ac;
	(void)av;
	args = malloc(sizeof(t_shell));
	args->new_env = malloc(sizeof(char *) * 256);
	args->env = ft_calloc(sizeof(char *), 256);
	args->new_env[0] = 0;
	args->env = env;
	config_signals();
	while (1)
	{
		args->input = readline("👾Phylothinkers👾> ");
		if (!cleandel(args))
			return (0);
		args->split = ft_split(args->input, ' ');
		if (args->input)
			add_history(args->input);
		check_valid_input(args);
		if (cmdhandler(args) == 0)
			return (0);
		freesformain(args);
	}
	rl_clear_history();
	return (0);
}
