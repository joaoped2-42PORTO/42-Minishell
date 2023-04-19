GREEN	=	\033[0;32m
RED 	=	\033[0;31m
YELLOW	=	\033[0;33m
RESET	=	\033[0m

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror


SRC		= src/main.c src/utils/utils.c src/commands/ls.c src/commands/cd.c src/commands/pwd.c
OBJ		= $(SRC:.c=.o)

all: $(OBJ)
		$(CC) $(CFLAGS) $(SRC) -lreadline -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re: fclean all
