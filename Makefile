GREEN	=	\033[0;32m
RED 	=	\033[0;31m
YELLOW	=	\033[0;33m
RESET	=	\033[0m

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror


SRC		= src/main.c src/utils/utils.c src/commands/cd.c src/commands/pwd.c src/handler/handler.c src/signals/signals.c
OBJ		= $(SRC:.c=.o)

all: $(OBJ)
		@echo "$(RED)[ .. ]Compiling Mandatory[ .. ]$(RESET)"
		@$(CC) $(CFLAGS) $(SRC) -lreadline -o $(NAME)
		@echo "$(GREEN)[ OK ]$(RESET)$(YELLOW)Mandatory Ready!$(RESET)$(GREEN)[ OK ]$(RESET)"

src/%.o:	src/%.c
			@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@echo "$(RED)[ .. ]Deleting objects[ .. ]$(RESET)"
	@rm -rf $(OBJ)
	@echo "$(GREEN)[ OK ]Objects deleted[ OK ]$(RESET)"

fclean: clean
	@echo "$(RED)[ .. ]Deleting Programs[ .. ]$(RESET)"
	@rm -rf $(NAME)
	@echo "$(GREEN)[ OK ]Programs deleted[ OK ]$(RESET)"

re: fclean all
