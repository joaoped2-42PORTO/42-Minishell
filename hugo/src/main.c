/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/04/27 23:01:12 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Neste momento ja se consegue alterar o directory onde nos encontramos,
// so que ainda nao funciona o cd sem mais nenhum argumento. Pelo que li,
// teremos que usar o env!

//CTRL+I = ls -la ???

/*void	check_valid_input(t_shell *args)
{
	int	i;
	int	j;
	int	k;
	int	x;

	i = 1;
	x = 0;
	args->argvs = malloc(sizeof(char *) * 256);
	while (args->split[i])
	{
		j = 0;
		k = ft_strlen(args->split[i]);
		args->argvs[x] = malloc(sizeof(char) * k);
		while (args->split[i][j])
		{
			if (args->split[i][0] == '"' || args->split[i][k] == '"')
				j++;
			else
			{
				args->argvs[x][j] = args->split[i][j];
				j++;
			}
		}
		x++;
		i++;
	}
	i = 0;
	while (args->argvs[i])
		printf("%s\n", args->argvs[i++]);
}*/

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_shell	*args;
	int	i = 0;

	args = malloc(sizeof(t_shell));
	config_signals();
	while (1)
	{
		args->input = readline("👾Phylothinkers👾> ");
		args->env = env;
		if (args->input == NULL)
		{
			free(args->input);
			printf("\n");
			return (0);
		}
		if (args->input)
			add_history(args->input);
		args->split = ft_split(args->input, ' ');
		//check_valid_input(args);
		if (cmdhandler(args) == 0)
			return (0);
		free(args->input);
	}
	while (args->split[i])
		printf("%s\n", args->split[i++]);
	return (0);
}
