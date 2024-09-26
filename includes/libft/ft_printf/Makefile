CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = ft_printf.a
SRC = ft_printf.c ft_putchar.c ft_puthex.c ft_putnbr.c ft_putstr.c ft_strlen.c ft_putptr.c ft_putunsnbr.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re