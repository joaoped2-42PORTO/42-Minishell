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
		hugo/src/commands/cd_utils.c

SRCJUAN = juanito/src/commands/cd.c \
		  juanito/src/commands/echo.c \
		  juanito/src/commands/env.c \
		  juanito/src/commands/export.c \
		  juanito/src/commands/export2.c \
		  juanito/src/commands/export3.c \
		  juanito/src/commands/pwd.c \
		  juanito/src/commands/unset.c \
		  juanito/src/handler/handler.c \
		  juanito/src/main/main.c \
		  juanito/src/main/main_utils.c \
		  juanito/src/signals/signals.c \
		  juanito/src/handler/tokens.c \
		  juanito/src/commands/echo_utils.c
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
		@$(CC) $(CFLAGS) $(SRCJUAN) $(LIBFT) -lreadline -o $(JSHELL)
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
