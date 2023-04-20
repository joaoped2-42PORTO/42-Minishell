/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/04/20 15:59:33 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Neste momento ja se consegue alterar o directory onde nos encontramos,
// so que ainda nao funciona o cd sem mais nenhum argumento. Pelo que li,
// teremos que usar o env!

//CTRL+I = ls -la ???


int	main(void)
{
	char	*input;

	config_signals();
	while (1)
	{
		input = readline("👾Phylothinkers👾> ");
		if (input == NULL)
		{
			free(input);
			printf("\n");
			return (0);
		}
		if (input == NULL)
		{
			free (input);
			printf("\n");
			return (0);
		}
		if (input && *input)
			add_history(input);
		if (cmdhandler(input) == 0)
			return (0);
		free(input);
	}
	return (0);
}
