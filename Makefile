# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 16:13:04 by aaleixo-          #+#    #+#              #
#    Updated: 2025/05/13 19:00:01 by fragarc2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SOURCES = \
	srcs/main.c srcs/builtins/echo.c \
	srcs/builtins/pwd.c srcs/builtins/cd.c \
	srcs/builtins/env.c srcs/builtins/exit.c \
	srcs/builtins/unset.c srcs/builtins/export.c \
	srcs/parsing.c srcs/execution.c srcs/utils.c \
	srcs/pipes.c srcs/utils2.c srcs/utils3.c \
	srcs/fd.c srcs/expand.c
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

fcount:
	@VAR1=$$(cat $(SOURCES) | wc -l); \
	echo "You have written $$VAR1 lines of code!"
