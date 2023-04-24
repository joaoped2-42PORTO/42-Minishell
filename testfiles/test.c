/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huolivei <huolivei <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:46:07 by joaoped2          #+#    #+#             */
/*   Updated: 2023/04/24 17:00:15 by huolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/*
		//verificar se um field descriptor esta a ser utilizado por um terminal
		//ou se e de um ficheiro.

void check_fd(int fd) {
  printf("fd %d is ", fd);
  if (!isatty(fd))
    printf("NOT ");
  puts("a tty");
}

int	main() {
  int p[2], fd;
  char fn[]="temp.file";

  if (pipe(p) != 0)
    perror("pipe() error");
  else {
    if ((fd = creat(fn, S_IWUSR)) < 0)
      perror("creat() error");
    else {
      check_fd(0);
      check_fd(fileno(stderr));
      check_fd(p[1]);
      check_fd(fd);
      close(fd);
      unlink(fn);
    }
    close(p[0]);
    close(p[1]);
  }
}

		//Retorna o ultimo erro dado pelo codigo!

int main(void)
{
	int fd;

	fd = open("te.txt", O_RDONLY);
	if (fd < 0)
		perror("Error");
	return(-1);
}


		//Ler o que esta em um directory e tambem conseguir saber tamanho e outras informacoes

int	main(void)
{
	char str[] = "/home/hugo/Desktop/42_common_core/Minishell-Phylothinkers";
	DIR	*i;
	struct dirent *j;
	i = opendir(str);
	while((j = readdir(i)) != NULL)
		printf("%s\n", j->d_name);
	closedir(i);
}


		//Pipe a funcionar com os processos parent e child!
#define MSGSIZE 16
char* msg1 = "hello, world #1";
char* msg2 = "hello, world #2";
char* msg3 = "hello, world #3";

int main()
{
    char inbuf[MSGSIZE];
    int p[2], pid, nbytes;

    if (pipe(p) < 0)
        exit(1);

    if ((pid = fork()) == 0) {
        write(p[1], msg1, MSGSIZE);
        write(p[1], msg2, MSGSIZE);
        write(p[1], msg3, MSGSIZE);

        // Adding this line will
        // not hang the program
		//close(p[1]);
		close(p[0]);
		//sleep(1);
    }
	waitpid(pid, NULL, 0);
        // Adding this line will
        // not hang the program
        close(p[1]);
        while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0)
            printf("%s\n", inbuf);
        close(p[0]);
		if (nbytes != 0)
            exit(2);
        printf("Finished reading\n");
    return 0;
}

int	main(void)
{
	//dup
	int	fd = open("texto.txt", O_WRONLY | O_APPEND);
	printf("%d\n", fd);

	int	cpy = dup(fd);
	printf("%d\n", cpy);
}

//correr executavel ou script de shell. TER ATENCAO AO ENVP! VERIFICAR A FUNDO!

int	main(void)
{
	char *temp[] = {"../hell","world",NULL};
	execve("hello", temp, NULL);
}


		//remove o ficheiro dado pelo path no caso de nao estar a ser utilizado por algum processo!
int	main(void)
{
	struct stat	str;
	int		rst;

	rst = unlink("/home/hugo/Desktop/42_common_core/Minishell-Phylothinkers/a.out");
	printf("%d\n", rst);
}


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
/*
int main(int argc,char **argv)
{
	struct dirent **namelist;
	int n;

	if(argc < 1)
	{
		exit(EXIT_FAILURE);
	}
	else if (argc == 1)
	{
		n=scandir(".",&namelist,NULL,alphasort);
	}
	else
	{
		n = scandir(argv[1], &namelist, NULL, alphasort);
	}
	if(n < 0)
	{
		perror("scandir");
		exit(EXIT_FAILURE);
	}
	else
	{
		while (n)
		{
			printf("%s\n",namelist[n]->d_name);
			free(namelist[n]);
		}
		free(namelist);
	}
	exit(EXIT_SUCCESS);
}*/

/*int main()
{
	int i = 0;
	char *str="ola/teste";
	while (str[i])
		i++;
	i--;
	while (str[i] != '/')
		i--;
	while (str[i])
		write(1, &str[i++], 1);
}*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char *path = getenv("HOME");
	printf("%s\n", path);
    //char *args[] = {"ls", "-l", NULL};
	(void)argc;
	(void)argv;
    /*if (execv(path, argv) < 0) {
        perror("execv");
        exit(1);
    }*/

    return 0;
}
