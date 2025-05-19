# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/15 20:17:12 by aherlaud          #+#    #+#              #
#    Updated: 2025/05/19 15:26:51 by aherlaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I libft

# MiniLibX paths
LIBFT_DIR = ../libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I $(LIBFT_DIR)

# Libraries
LIBS = -L$(LIBFT_DIR) -lft

# Source and object files
SRCS = execute_cmd.c here_doc.c split_cmd.c main.c

OBJS = $(SRCS:.c=.o)

# Executable name
NAME = pipex

# Build rules
all: $(LIBFT_LIB) $(NAME)

$(LIBFT_LIB):
	make -C $(LIBFT_DIR)

# Compile object files with MiniLibX includes
%.o: %.c
	$(CC) -g $(CFLAGS) $(LIBFT_INC) -c $< -o $@

# Link executable
$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR)

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all
