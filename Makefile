GREEN	=	\033[0;32m
RED 	=	\033[0;31m
YELLOW	=	\033[0;33m
RESET	=	\033[0m

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

HSHELL  = hugoshell
JSHELL  = juanitoshell

SRC		= src/main.c src/utils/utils.c src/commands/cd.c src/commands/pwd.c src/handler/handler.c src/signals/signals.c
SRCHUGO = hugo/src/main.c hugo/src/utils/utils.c hugo/src/commands/cd.c hugo/src/commands/pwd.c hugo/src/handler/handler.c hugo/src/signals/signals.c
SRCJUAN = juanito/src/main.c juanito/src/utils/utils.c juanito/src/commands/cd.c juanito/src/commands/pwd.c juanito/src/handler/handler.c juanito/src/signals/signals.c
OBJ		= $(SRC:.c=.o)
OBJHUGO = $(SRCHUGO:.c=.o)
OBJUAN	= $(SRCJUAN:.c=.o)

all: $(OBJ)
		@echo "$(RED)[ .. ]Compiling Mandatory[ .. ]$(RESET)"
		@$(CC) $(CFLAGS) $(SRC) -lreadline -o $(NAME)
		@echo "$(GREEN)[ OK ]$(RESET)$(YELLOW)Mandatory Ready!$(RESET)$(GREEN)[ OK ]$(RESET)"

hugo: $(OBJHUGO)
		$(CC) $(CFLAGS) $(SRCHUGO) -lreadline -o $(HSHELL)

juan: $(OBJUAN)
		$(CC) $(CFLAGS) $(SRCJUAN) -lreadline -o $(JSHELL)

src/%.o:	src/%.c
			@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@echo "$(RED)[ .. ]Deleting objects[ .. ]$(RESET)"
	@rm -rf $(OBJ) $(OBJHUGO) $(OBJUAN)
	@echo "$(GREEN)[ OK ]Objects deleted[ OK ]$(RESET)"

fclean: clean
	@echo "$(RED)[ .. ]Deleting Programs[ .. ]$(RESET)"
	@rm -rf $(NAME) $(JSHELL) $(HSHELL)
	@echo "$(GREEN)[ OK ]Programs deleted[ OK ]$(RESET)"

re: fclean all
