FLAGS = -Wall -Wextra -Werror

CC = cc

NAME = libftprintf.a

SRC	 = ft_printf_fd.c put_printf.c put_hexptr.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) -c $(SRC)
	ar rcs $(NAME) $(OBJ)

main: all
	$(CC) $(FLAGS) -L. $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME) a.out

re: fclean all

# gcc:
# 	gcc $(FLAGS) -g $(SRC) $(HEADER)
# 	ar rcs $(NAME) $(OBJ)

.PHONY:			all clean fclean re bonus