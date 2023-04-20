/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/04/20 14:28:15 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Neste momento ja se consegue alterar o directory onde nos encontramos,
// so que ainda nao funciona o cd sem mais nenhum argumento. Pelo que li,
// teremos que usar o env!

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	config_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	char	*input;

	(void)ac;
	(void)av;
	(void)env; //CUIDADO!
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
		if (input && *input)
			add_history(input);
		if (!ft_strncmp(input, "pwd", 3))
			check_pwd();
		else if (!ft_strncmp(input, "cd ", 3))
			do_cd(input);
		else if (!ft_strncmp(input, "cd", 2))
		{
			chdir("/nfs/homes/");
			printf("OI!\n");
		}
		else if (!ft_strncmp(input, "exit", 4))
			return (0);
		else if (!ft_strncmp(input, "ls", 2))
			check_files_in_path(input);
		else
			printf("command not found: %s\n", input);
		free(input);
	}
	return (0);
}
