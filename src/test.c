/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:46:07 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/14 11:37:31 by joaoped2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("👾Phylothinkers👾> ");
		if (input && *input)
			add_history(input);
		if (!ft_strncmp(input, "clear", 5))
			system("clear");
		else
			printf("command not found: %s\n", input);
		free(input);
	}
	return (0);
}
/*
	#include <stdlib.h>
	int system(const char *command);

	The system() library function uses fork(2) to create a child
	process that executes the shell command specified in command
	using execl(3) as follows:

		execl("/bin/sh", "sh", "-c", command, (char *) NULL);
*/
/*
//Criar o prompt necessario para inicializar o Shell
int main()
{
	char *str = readline("$");
	rl_replace_line("%%", 1);
	add_history(str);
	rl_clear_history();
	rl_on_new_line();
	rl_redisplay();
	printf("%s eliminada;\n", str);
	free(str);
}*/
