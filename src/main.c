/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 22:11:07 by huolivei          #+#    #+#             */
/*   Updated: 2023/04/19 16:28:35 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Neste momento ja se consegue alterar o directory onde nos encontramos,
// so que ainda nao funciona o cd sem mais nenhum argumento. Pelo que li,
// teremos que usar o env!

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("👾Phylothinkers👾> ");
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
		else if (!ft_strncmp(input, "ls", 2) || (!ft_strncmp(input, "/bin/ls", 7))
			check_files_in_path(input);
		else
			printf("command not found: %s\n", input);
		free(input);
	}
	return (0);
}
