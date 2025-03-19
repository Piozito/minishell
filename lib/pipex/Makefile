# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 13:30:31 by aaleixo-          #+#    #+#              #
#    Updated: 2025/03/19 13:30:31 by aaleixo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = pipex
SOURCES = \
	srcs/pipex.c srcs/utils.c
OBJECTS = $(SOURCES:.c=.o)

MAKE_PRINTF = make -C ./libft

CC = cc
CFLAGS = -Wall -Wextra -Werror
ADLIBS = ./libft/libft.a

all: $(NAME)

$(ADLIBS):
	$(MAKE_PRINTF)

$(NAME): $(OBJECTS) $(ADLIBS)
	$(CC) $(CFLAGS) $(OBJECTS) $(ADLIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	$(MAKE_PRINTF) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE_PRINTF) fclean

re: fclean all

.PHONY: all clean fclean re