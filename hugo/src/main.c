/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/04/24 16:09:03 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Neste momento ja se consegue alterar o directory onde nos encontramos,
// so que ainda nao funciona o cd sem mais nenhum argumento. Pelo que li,
// teremos que usar o env!

//CTRL+I = ls -la ???

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)env;
	(void)av;
	t_shell	*args;
	int	i = 0;

	args = malloc(sizeof(t_shell));
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
		args->split = ft_split(args->input, ' ');
		if (cmdhandler(args) == 0)
			return (0);
		free(args->input);
	}
	while (args->split[i])
		printf("%s\n", args->split[i++]);
	return (0);
}
