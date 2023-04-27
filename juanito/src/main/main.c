/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/04/27 14:42:41 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	minishell(char **env)
{
	t_shell	*args;
	int		i;

	args = malloc(sizeof(t_shell));
	i = 0;
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
		if (cmdhandler(args) == 0)
			return (0);
		free(args->input);
	}
	while (args->split[i])
		printf("%s\n", args->split[i++]);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	config_signals();
	minishell(env);
}
