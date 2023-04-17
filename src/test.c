/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:46:07 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/17 23:12:35 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	struct stat	str;
	int		rst;

	rst = stat("/home/hugo/Desktop/42_common_core/Minishell-Phylothinkers/test.c", &str);
	printf("%d\n%ld\n", rst, str.st_blksize);
}

/*
		//Ver o caminho que nos encontramos e alterar o mesmo caso necessario!!

int	main(void)
{
	char	path[200];
	int	error;
	getcwd(path, sizeof(path));
	printf("Onde nos encontramos: %s\n", path);
	chdir("..");
	getcwd(path, sizeof(path));
	printf("Para onde fomos: %s\n", path);
	error = chdir("Minishell-Phylothinkers");
	getcwd(path, sizeof(path));
	printf("Para onde fomos: %s\n %d\n", path, error);
	error = chdir("Minishell-Phylothinkers");
	getcwd(path, sizeof(path));
	printf("Para onde fomos: %s\n %d\n", path, error); // testar o erro da mudanca de caminho!
	return (0);
}

		//criar novos processos com o menor numero possiveis de processos zombies

int	main(void)
{
	pid_t qq[5];
	int	i, rst;
	i = rst = 0;
	while (i < 5)
	{
		if ((qq[i] = fork()) == 0)
		{
			printf("Fui criado com o numero %d e o pid %d\n", i, qq[i]);
			exit(1);	// obrigatorio para nao estar a criar processos zombies, claro que poderia ser outra opcao!!
		}
		else
			printf("Sou um zombie\n"); //verificar os processos zombies
		sleep(1);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pid_t pid = waitpid(qq[i], &rst, 1);
		printf("%d exit status : %d\n", pid, rst);
		i++;
	}
	return 0;
}

		//verificar se o acesso aos ficheiros foi bem sucedido!

int	main(void)
{
	//correcto
	int rst = access("/home/hugo/Desktop/42_common_core/Minishell-Phylothinkers/test.c", F_OK);
	//erro
	int rst1 = access("/home/hugo/Desktop/42_common_core/Minishell-Phylothinkers/test.c", X_OK);
	printf("%d\n%d\n", rst, rst1);
}

		//Prompt mais chique

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
