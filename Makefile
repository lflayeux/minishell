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
		src/utils/init_2.c \
		src/utils/init_pid.c \
		src/error/error.c \
		src/tokenization/lst_tok.c \
		src/tokenization/tokenize.c \
		src/tokenization/tokenize_utils.c \
		src/expansion/expansion.c \
		src/expansion/expand_utils.c \
		src/expansion/expand_var.c \
		src/expansion/expand_part.c \
		src/execution/prepare_exec.c \
		src/execution/prepare_exec_utils.c \
		src/execution/lst_exec.c \
		src/pipex_modif/pipex.c \
		src/pipex_modif/pipex_utils.c \
		src/pipex_modif/here_doc.c \
		src/pipex_modif/execute_cmd.c \
		src/built_in/built_in.c \
		src/built_in/built_in_exit.c \
		src/built_in/built_in_pwd.c \
		src/built_in/built_in_cd.c \
		src/built_in/built_in_echo.c \
		src/built_in/built_in_env.c \
		src/built_in/built_in_export.c \
		src/built_in/built_in_unset.c \
		src/built_in/built_in_utils.c \
		src/built_in/built_in_utils_2.c \

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

valg : re
	@valgrind --leak-check=full --show-leak-kinds=all \
	--suppressions=rl_leak.supp --trace-children=yes --track-fds=yes ./minishell

.PHONY: clean fclean re