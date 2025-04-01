# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 16:13:04 by aaleixo-          #+#    #+#              #
#    Updated: 2025/04/01 17:06:28 by aaleixo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SOURCES = \
	srcs/main.c srcs/builtins/echo.c \
	srcs/builtins/pwd.c srcs/builtins/cd.c \
	srcs/builtins/env.c srcs/builtins/exit.c \
	srcs/builtins/unset.c srcs/builtins/export.c \
	srcs/parsing.c srcs/execution.c srcs/utils.c \
	srcs/pipes.c
OBJECTS = $(SOURCES:.c=.o)

MAKE_PRINTF = make -C ./lib/pipex/

CC = cc
CFLAGS = -Wall -Wextra -Werror
ADLIBS = ./lib/pipex/libft/libft.a

all: $(NAME)

$(ADLIBS):
	$(MAKE_PRINTF)

$(NAME): $(OBJECTS) $(ADLIBS)
	$(CC) $(CFLAGS) $(OBJECTS) $(ADLIBS) -o $(NAME) -lreadline

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