# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 16:13:04 by aaleixo-          #+#    #+#              #
#    Updated: 2025/04/10 16:08:39 by aaleixo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SOURCES = \
	srcs/main.c srcs/builtins/echo.c \
	srcs/builtins/pwd.c srcs/builtins/cd.c \
	srcs/builtins/env.c srcs/builtins/exit.c \
	srcs/builtins/unset.c srcs/builtins/export.c \
	srcs/parsing.c srcs/execution.c srcs/utils.c \
	srcs/pipes.c srcs/utils2.c \
	srcs/redir.c
OBJECTS = $(SOURCES:.c=.o)

MAKE_LIBFT = make -C ./lib/libft/

CC = cc
CFLAGS = -Wall -Wextra -Werror
ADLIBS = ./lib/libft/libft.a

all: $(NAME)

$(ADLIBS):
	$(MAKE_LIBFT)

$(NAME): $(OBJECTS) $(ADLIBS)
	$(CC) $(CFLAGS) $(OBJECTS) $(ADLIBS) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	$(MAKE_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re