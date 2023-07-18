GREEN       =   \033[0;32m
RED         =   \033[0;31m
YELLOW      =   \033[0;33m
RESET       =   \033[0m

NAME        = minishell
CC          = cc -g
CFLAGS      = -Wall -Wextra -Werror

SRC         = src/cleaner/cleaner.c \
              src/cleaner/cleaner2.c \
              src/commands/cd_utils.c \
              src/commands/cd.c \
              src/commands/echo_checker.c \
              src/commands/echo_utils.c \
              src/commands/echo.c \
              src/commands/export_utils.c \
              src/commands/export_utils2.c \
              src/commands/export_utils3.c \
              src/commands/export.c \
              src/commands/pwd.c \
              src/commands/unset_utils.c \
              src/commands/unset.c \
			  src/handler/expander_utils.c \
              src/handler/expander.c \
              src/handler/handler.c \
              src/handler/handler_utils.c \
              src/handler/handler_utils2.c \
              src/handler/handler_utils3.c \
              src/handler/handler_utils4.c \
              src/handler/handler_utils5.c \
              src/handler/handler_utils6.c \
              src/handler/pipes_utils.c \
              src/handler/pipes_utils2.c \
			  src/handler/pipes_utils3.c \
              src/handler/pipes.c \
              src/handler/tokens.c \
              src/handler/tokens2.c \
              src/handler/tokens3.c \
              src/handler/tokens4.c \
              src/init_and_checker/checker.c \
              src/init_and_checker/init_utils.c \
              src/init_and_checker/init.c \
              src/init_and_checker/redir.c \
              src/init_and_checker/utils.c \
              src/signals/signals.c \
              src/main_utils3.c \
              src/main_utils2.c \
              src/main_utils.c \
              src/main.c

OBJDIR      = obj
OBJ         = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
LIBFT       = libft/libft.a
LIBFT_DIR   = libft

all: $(NAME)
#-fsanitize=address
$(NAME): $(OBJ)
	@make -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@echo "${GREEN}Minishell Compilation Complete! ${RESET}"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -s clean -C $(LIBFT_DIR)
	@rm -rf $(OBJDIR)
	@echo "${RED}Objects Deleted!${RESET}"

fclean: clean
	@make -s fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)
	@echo "${RED}Program Deleted!${RESET}"

re: fclean all
