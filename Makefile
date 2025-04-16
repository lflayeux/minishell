CC = cc

INCLUDE =	-I./libft

CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDE)

RL_FLAGS = -lreadline

NAME = minishell

SRC =	main.c \
		signals.c \
		signals_utils.c 

GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
RESET = \033[0m

OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libft

LIBFT_A = $(LIBFT_DIR)/libft.a

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $< 

$(NAME) : $(OBJ) $(LIBFT_A)
	@$(CC) $(CFLAGS) -o $@ $^ $(RL_FLAGS)
	@echo "$(GREEN)Compilation successful ! ✅ $(RESET)"

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

all : $(NAME)

clean :
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory 
	@echo "$(YELLOW)All object files cleaned. 🧹$(RESET)"

fclean : clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory 
	@echo "$(YELLOW)Executable cleaned. 🧹$(RESET)"

re : fclean all

.PHONY: clean fclean re
