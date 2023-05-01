/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/05/01 16:23:19 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Neste momento ja se consegue alterar o directory onde nos encontramos,
// so que ainda nao funciona o cd sem mais nenhum argumento. Pelo que li,
// teremos que usar o env!

//CTRL+I = ls -la ???

int	check_max_string(t_shell *args)
{
	int	i;

	i = 0;
	while(args->split[i])
		i++;
	return (i);
}

void	check_valid_input(t_shell *args)
{
	int	j;
	int	x;
	int	y;
	int	flag;

	y = 0;
	x = 0;
	j = 0;
	args->exp = ft_calloc(ft_strlen(args->input), sizeof(char));
	args->split = ft_split(args->input, ' ');
	while (args->split[x])
	{
		j = 0;
		flag = 0;
		while (args->split[x][j])
		{
			if (args->split[x][j] == '"')
			{
				j++;
				while(1)
				{
					if (args->split[x] == 0)
						break ;
					while(args->split[x][j] != '"')
					{
						flag = 1;
						args->exp[y] = args->split[x][j];
						j++;
						y++;
						if (args->split[x][j] == '\0')
							break ;
					}
					if (flag == 1)
						args->exp[y++] = ' ';
					j = 0;
					x++;
				}
				flag = 1;
			}
			if (args->split[x] == 0)
						break ;
			j++;
		}
	}
	args->exp = ft_strtrim(args->exp, " ");
	printf("%s\n", args->exp);
}


int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_shell	*args;

	args = malloc(sizeof(t_shell));
	args->env = env;
	config_signals();
	while (1)
	{
		args->input = readline("👾Phylothinkers👾> ");
		if (args->input == NULL)
		{
			free(args->input);
			printf("\n");
			return (0);
		}
		if (args->input)
			add_history(args->input);
		check_valid_input(args);
		/*if (cmdhandler(args) == 0)
			return (0);*/
		free(args->input);
	}
	rl_clear_history();
	return (0);
}
