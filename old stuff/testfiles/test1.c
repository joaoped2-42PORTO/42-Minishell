#include "../includes/minishell.h"

int	main(int ac, char **av)
{
	if (ac > 1)
		printf("Funcionou!\nav[0]: %s\nav[1]: %s\n",av[0], av[1]);
	else
		printf("Nao funcinou!\n");
	return (0);
}
