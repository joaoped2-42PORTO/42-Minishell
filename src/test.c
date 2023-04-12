#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main()
{
    char *input;

    while ((input = readline("👾Phylothinkers👾> ")) != NULL) {
        printf("You entered: %s\n", input);
        free(input);
    }

    return 0;
}
