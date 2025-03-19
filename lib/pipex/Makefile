NAME = pipex

CC = gcc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS = 	src/pipex.c \
		src/utils.c \
		lib/libft/libft.a \

$(NAME) :
	make all -C ./lib/libft
	gcc $(CFLAGS) $(SRCS) -o $(NAME)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C ./lib/libft

clean :
	$(RM) $(NAME)
	make clean -C ./lib/libft

re : fclean all