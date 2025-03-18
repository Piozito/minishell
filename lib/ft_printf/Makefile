# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/09 11:29:01 by aaleixo-          #+#    #+#              #
#    Updated: 2025/03/09 18:05:42 by aaleixo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c ft_putnbr.c ft_ptr.c 
OBJS = $(SRCS:.c=.o)

MAKE_GNL = make -C ./get_next_line
MAKE_LIBFT = make -C ./libft

GNL = get_next_line/get_next_line.a
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL)
	ar rsc $(NAME) $(OBJS) libft/*.o get_next_line/*.o

$(LIBFT):
	$(MAKE_LIBFT)

$(GNL):
	$(MAKE_GNL)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE_GNL) clean
	$(MAKE_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE_GNL) fclean
	$(MAKE_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re