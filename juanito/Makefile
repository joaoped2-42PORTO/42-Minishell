.SILENT:

GREEN	=	\033[0;32m
RED 	=	\033[0;31m
YELLOW	=	\033[0;33m
RESET	=	\033[0m

NAME	= minishell
CC		= cc -g
CFLAGS	= -Wall -Wextra -Werror

HSHELL  = hugoshell
JSHELL  = juanitoshell

SRC		= src/main.c src/commands/cd.c src/commands/pwd.c src/handler/handler.c src/signals/signals.c
SRCHUGO = hugo/src/main.c hugo/src/commands/cd.c hugo/src/commands/pwd.c hugo/src/handler/handler.c hugo/src/signals/signals.c \
		hugo/src/commands/export.c hugo/src/commands/export_utils.c hugo/src/commands/unset.c hugo/src/commands/unset_utils.c \
		hugo/src/commands/cd_utils.c hugo/src/init_and_checker/init.c hugo/src/init_and_checker/init_utils.c \
		hugo/src/cleaner/cleaner.c hugo/src/init_and_checker/checker.c \
		hugo/src/handler/tokens.c \
		hugo/src/handler/tokens2.c \
		hugo/src/handler/tokens3.c
SRCJUAN = juanito/src/cleaner/cleaner.c\
		  juanito/src/commands/cd_utils.c\
		  juanito/src/commands/cd.c \
		  juanito/src/commands/echo_checker.c\
		  juanito/src/commands/echo_utils.c\
		  juanito/src/commands/echo.c \
		  juanito/src/commands/export_utils.c\
		  juanito/src/commands/export.c \
		  juanito/src/commands/export2.c \
		  juanito/src/commands/pwd.c \
		  juanito/src/commands/unset_utils.c \
		  juanito/src/commands/unset.c \
		  juanito/src/handler/handler.c \
		  juanito/src/handler/handler2.c \
		  juanito/src/handler/handler3.c \
		  juanito/src/handler/handler4.c \
		  juanito/src/handler/pipes.c \
		  juanito/src/handler/tokens.c \
		  juanito/src/handler/tokens2.c \
		  juanito/src/handler/tokens3.c \
		  juanito/src/handler/tokens4.c \
		  juanito/src/handler/utils.c \
		  juanito/src/init_and_checker/checker_utils.c \
		  juanito/src/init_and_checker/checker.c \
		  juanito/src/init_and_checker/init_utils.c \
		  juanito/src/init_and_checker/init.c \
		  juanito/src/signals/signals.c \
		  juanito/src/main_utils.c \
		  juanito/src/main.c

OBJ		= $(SRC:.c=.o)
OBJHUGO = $(SRCHUGO:.c=.o)
OBJUAN	= $(SRCJUAN:.c=.o)
LIBFT = libft/libft.a
LIBFT_DIR = libft

all: $(OBJ)
		$(MAKE) -C $(LIBFT_DIR)
		@$(CC) $(CFLAGS) $(SRC) -lreadline -fsanitize=address -o $(NAME)
		@echo Compilation Complete!

hugo: $(OBJHUGO)
		$(MAKE) -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) $(SRCHUGO) $(LIBFT) -lreadline -fsanitize=address -o $(HSHELL)
		@echo Compilation Complete!

juan: $(OBJUAN)
		@make -s -C $(LIBFT_DIR)
		@$(CC) $(CFLAGS) $(SRCJUAN) $(LIBFT) -lreadline -fsanitize=address -o $(JSHELL)
		@echo "${GREEN}Minishell Compilation Complete! ${RESET}"

src/%.o:	src/%.c
			@$(CC) $(CFLAGS) -o $@ -c $<

juanito/src/%.o:	juanito/src/%.c
			@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@make -s clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ) $(OBJHUGO) $(OBJUAN)
	@echo "${RED}Objects Deleted!${RESET}"

fclean: clean
	@make -s fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME) $(JSHELL) $(HSHELL)
	@echo "${RED}Program deleted!${RESET}"

re: fclean all

rej: fclean juan
