CC = cc

INCLUDE =	-I./libft

CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDE)

RL_FLAGS = -lreadline

NAME = minishell

SRC =	src/main.c \
		src/signals.c \
		src/signals_utils.c \
		src/tokenize.c \
		src/lst_tok.c \
		src/word_parsing.c \
		src/lst_exec.c \
		src/pipe_process.c \
		src/built_in.c

GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
RESET = \033[0m

OBJ_DIR = build/

OBJ = $(SRC:src/%.c=$(OBJ_DIR)%.o)

LIBFT_DIR = ./libft

LIBFT_A = $(LIBFT_DIR)/libft.a

$(OBJ_DIR)%.o : src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(LIBFT_A)
	@$(CC) $(CFLAGS) -o $@ $^ $(RL_FLAGS)
	@echo "$(GREEN)Compilation successful ! ✅ $(RESET)"

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

all : $(NAME)

clean :
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory 
	@echo "$(YELLOW)All object files cleaned. 🧹$(RESET)"

fclean : clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory 
	@echo "$(YELLOW)Executable cleaned. 🧹$(RESET)"

re : fclean all

.PHONY: clean fclean re


