# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 16:13:04 by aaleixo-          #+#    #+#              #
#    Updated: 2025/03/18 16:13:04 by aaleixo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SOURCES = \
	main.c
OBJECTS = $(SOURCES:.c=.o)

MAKE_PRINTF = make -C ./lib/libft

CC = cc
CFLAGS = -Wall -Wextra -Werror
ADLIBS = ./lib/libft/libft.a

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