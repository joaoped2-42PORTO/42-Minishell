#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	main()
{
	char *str;
	str = readline(str);
	printf("%s\n", str);
	free (str);
}
