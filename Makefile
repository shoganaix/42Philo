# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 19:11:17 by msoriano          #+#    #+#              #
#    Updated: 2024/08/20 20:37:20 by msoriano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

LIB = -lpthread

SRC = src/main.c \
		src/philo.c \
		src/checks.c \
		src/libft_utils.c \
		src/utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

RM = rm -f

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all printf clean fclean re