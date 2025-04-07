CC = cc
CFLAGS = -Wall -Werror -Wextra
NAME = libft.a
SRC =	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_putchar.c \
		ft_putnbr.c \
		ft_putnbrhexa.c \
		ft_putnbrhexa_up.c \
		ft_putstr.c \
		ft_printf.c \
		ft_strcmp.c \
		ft_free_tab.c

BONUS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
RESET = \033[0m

ALL_FILES = $(SRC) $(BONUS)

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(ALL_FILES:.c=.o)

$(NAME) : $(OBJ)
	@ar -rcs -o $@ $^
	@echo "$(GREEN)libft.a created successfully ! ✅ $(RESET)"

bonus : $(OBJ_BONUS)
	@ar -rcs -o $(NAME) $^

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

clean :
	@rm -f $(OBJ) $(OBJ_BONUS)
	@echo "$(YELLOW)libft object files cleaned. 🧹$(RESET)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(YELLOW)libft cleaned. 🧹$(RESET)"

re : fclean all
