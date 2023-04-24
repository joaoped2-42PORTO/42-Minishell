GREEN	=	\033[0;32m
RED 	=	\033[0;31m
YELLOW	=	\033[0;33m
RESET	=	\033[0m

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

HSHELL  = hugoshell
JSHELL  = juanitoshell

SRC		= src/main.c src/commands/cd.c src/commands/pwd.c src/handler/handler.c src/signals/signals.c
SRCHUGO = hugo/src/main.c hugo/src/commands/cd.c hugo/src/commands/pwd.c hugo/src/handler/handler.c hugo/src/signals/signals.c
SRCJUAN = juanito/src/main.c juanito/src/commands/cd.c juanito/src/commands/pwd.c juanito/src/handler/handler.c juanito/src/signals/signals.c
OBJ		= $(SRC:.c=.o)
OBJHUGO = $(SRCHUGO:.c=.o)
OBJUAN	= $(SRCJUAN:.c=.o)
LIBFT = libft/libft.a
LIBFT_DIR = libft

all: $(OBJ)
		$(MAKE) -C $(LIBFT_DIR)
		@echo "$(RED)[ .. ]Compiling Mandatory[ .. ]$(RESET)"
		@$(CC) $(CFLAGS) $(SRC) -lreadline -o $(NAME)
		@echo "$(GREEN)[ OK ]$(RESET)$(YELLOW)Mandatory Ready!$(RESET)$(GREEN)[ OK ]$(RESET)"

hugo: $(OBJHUGO)
		$(MAKE) -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) $(SRCHUGO) $(LIBFT) -lreadline -o $(HSHELL)

juan: $(OBJUAN)
		$(MAKE) -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) $(SRCJUAN) $(LIBFT) -lreadline -o $(JSHELL)

src/%.o:	src/%.c
			@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(RED)[ .. ]Deleting objects[ .. ]$(RESET)"
	@rm -rf $(OBJ) $(OBJHUGO) $(OBJUAN)
	@echo "$(GREEN)[ OK ]Objects deleted[ OK ]$(RESET)"

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)[ .. ]Deleting Programs[ .. ]$(RESET)"
	@rm -rf $(NAME) $(JSHELL) $(HSHELL)
	@echo "$(GREEN)[ OK ]Programs deleted[ OK ]$(RESET)"

re: fclean all

rej: fclean juan
