CC = cc

INCLUDE =	-I./libft

CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDE)

RL_FLAGS = -lreadline

NAME = minishell

SRC =	src/main.c \
		src/signals/signals.c \
		src/signals/signals_utils.c \
		src/tokenization/tokenize.c \
		src/tokenization/lst_tok.c \
		src/expansion/expansion.c \
		src/expansion/expansion_utils.c \
		src/expansion/expansion_utils2.c \
		src/built_in/built_in.c \
		src/built_in/built_in_env.c \
		src/built_in/built_in_utils.c \
		src/lst/lst_malloc.c \
		src/lst/lst_exec.c \
		src/free_all.c \
		src/pipe_process.c \
		src/init.c \
		pipex_modif/execute_cmd.c \
		pipex_modif/here_doc.c \
		pipex_modif/pipex.c \
		# pipex_modif/split_cmd.c \


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
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory 
	@echo "$(YELLOW)All object files cleaned. 🧹$(RESET)"

fclean : clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory 
	@echo "$(YELLOW)Executable cleaned. 🧹$(RESET)"

re : fclean all

.PHONY: clean fclean re