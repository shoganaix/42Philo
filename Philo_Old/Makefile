# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 19:11:17 by msoriano          #+#    #+#              #
#    Updated: 2024/11/20 18:20:40 by msoriano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m

LIB = -lpthread

SRC = src/main.c \
		src/philo.c \
		src/checks.c \
		src/libft_utils.c \
		src/utils.c \

OBJ = $(SRC:.c=.o)

COLORS = $(RED) $(GREEN) $(YELLOW) $(BLUE)
COLOR_INDEX = 0

# all: credit $(NAME)
 all: $(NAME)


$(NAME): $(OBJ)
	@echo "$(GREEN)Creating executable $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)

%.o: %.c
	@printf "$(YELLOW)Compiling: $<$(RESET)\n"
	$(CC) $(CFLAGS) -c -o $@ $<

RM = rm -f

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	$(RM) $(OBJ)

fclean: clean
	@echo "$(RED)Removing executable...$(RESET)"
	$(RM) $(NAME)

re: fclean all

.PHONY: all printf clean fclean re

credit:
	@echo "                                                                                           "
	@echo "▀██▀▀█▄  ▀██       ██  ▀██                                  ▀██"
	@echo " ██   ██  ██ ▄▄   ▄▄▄   ██    ▄▄▄    ▄▄▄▄    ▄▄▄   ▄▄▄ ▄▄▄   ██ ▄▄     ▄▄▄▄  ▄▄▄ ▄▄   ▄▄▄▄"
	@echo " ██▄▄▄█▀  ██▀ ██   ██   ██  ▄█  ▀█▄ ██▄ ▀  ▄█  ▀█▄  ██▀  ██  ██▀ ██  ▄█▄▄▄██  ██▀ ▀▀ ██▄ ▀"
	@echo " ██       ██  ██   ██   ██  ██   ██ ▄ ▀█▄▄ ██   ██  ██    █  ██  ██  ██       ██     ▄ ▀█▄▄"
	@echo "▄██▄     ▄██▄ ██▄ ▄██▄ ▄██▄  ▀█▄▄█▀ █▀▄▄█▀  ▀█▄▄█▀  ██▄▄▄▀  ▄██▄ ██▄  ▀█▄▄▄▀ ▄██▄    █▀▄▄█▀"
	@echo "                                                    ██"
	@echo "                                                    ██"
