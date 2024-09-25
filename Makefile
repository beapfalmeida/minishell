CC = cc
CFLAGS = -Wextra -Wall -Werror -g

READLINE_PATH = vendor/readline/
RLFLAG = -L$(READLINE_PATH)/lib -lreadline

SRC = jsobreir-main.c init.c
OBJ = $(SRC:.c=.o)

NAME = minishell
LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a
FT_PRINTF_DIR = $(LIBFT_DIR)/ft_printf
FT_PRINTF_A = $(FT_PRINTF_DIR)/ft_printf.a

all: libft $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) $(FT_PRINTF_A)
	$(CC) $(CFLAGS) $(RLFLAG) $(OBJ) $(LIBFT_A) $(FT_PRINTF_A) -o $(NAME)

$(LIBFT_A): libft
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	@if [-d "$(LIBFT_DIR)"]; then \
	$(MAKE) -C $(LIBFT_DIR) clean; \
	fi

fclean: clean
	rm -f $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then \
	$(MAKE) -C $(LIBFT_DIR) fclean; \
	fi

re: fclean all
