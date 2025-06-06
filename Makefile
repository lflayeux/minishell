CC = cc

INCLUDE =	-I./libft

CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDE)

RL_FLAGS = -lreadline

NAME = minishell

SRC =	src/main.c \
		src/signals/signals.c \
		src/signals/signals_utils.c \
		src/utils/free.c \
		src/utils/init.c \
		src/error/error.c \
		src/tokenization/lst_tok.c \
		src/tokenization/tokenize.c \
		src/tokenization/tokenize_utils.c \

GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
RESET = \033[0m

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

build/pipex_modif/%.o: pipex_modif/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

OBJ = $(SRC:.c=.o)
OBJ := $(OBJ:src/%=build/%)
OBJ := $(OBJ:pipex_modif/%=build/pipex_modif/%)


LIBFT_DIR = ./libft

LIBFT_A = $(LIBFT_DIR)/libft.a

$(OBJ_DIR)%.o : src/%/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) $(LIBFT_A)
	@$(CC) $(CFLAGS) -o $@ $^ $(RL_FLAGS)
	@echo "$(GREEN)Compilation successful ! ✅ $(RESET)"

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

all : $(NAME)

clean :
	@rm -rf build/
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory 
	@echo "$(YELLOW)All object files cleaned. 🧹$(RESET)"

fclean : clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory 
	@echo "$(YELLOW)Executable cleaned. 🧹$(RESET)"

re : fclean all

.PHONY: clean fclean re