GREEN	=	\033[0;32m
RED 	=	\033[0;31m
YELLOW	=	\033[0;33m
RESET	=	\033[0m

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror


SRC		= src/test.c
OBJ		= $(SRC:.c=.o)

all: $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re: fclean all
