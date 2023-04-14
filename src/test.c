#include "../includes/minishell.h"

int main()
{
    char *input;

    while ((input = readline("👾Phylothinkers👾> ")) != NULL) {
		if (input && *input)
			add_history(input);
		if (!strcmp(input, "history")) { system("history"); }
		else if (!strcmp(input, "ifconfig")) { system("ifconfig"); }
		else if (!strcmp(input, "clear")) { system("clear"); }
        else
			printf("%s\n", input);
        free(input);
    }

    return 0;
}
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
