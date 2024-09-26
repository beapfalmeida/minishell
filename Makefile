CC = cc

CFLAGS = -Wextra -Wall -Werror -g

READLINE_PATH = vendor/readline/
RLFLAG = -L$(READLINE_PATH)/lib -lreadline


NAME = minishell

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a
# Retirei o printf pois podemos usar a funcao original

# Directories containing source files
SRC_DIR = src
EXECUTOR_DIR = $(SRC_DIR)/executor
PARSER_DIR = $(SRC_DIR)parser
INIT_DIR = $(SRC_DIR)/init

# Directory for obj files
OBJ_DIR = obj

# ------------------------------------------------------------------- #
# ------------------------------ Files ------------------------------ #
# ------------------------------------------------------------------- #
SRC = jsobreir/jsobreir-main.c \
      $(SRC_DIR)/$(INIT_DIR)/init.c \
      $(SRC_DIR)/$(EXECUTOR_DIR)/executor.c \
      $(SRC_DIR)/$(EXECUTOR_DIR)/pwd/handle_pwd.c \

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all: libft $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) $(FT_PRINTF_A)
	$(CC) $(CFLAGS) $(RLFLAG) $(OBJ) $(LIBFT_A) $(FT_PRINTF_A) -o $(NAME)

$(LIBFT_A): libft
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	@if [ -d "$(LIBFT_DIR)" ]; then \
	$(MAKE) -C $(LIBFT_DIR) clean; \
	fi

fclean: clean
	rm -f $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then \
	$(MAKE) -C $(LIBFT_DIR) fclean; \
	fi

re: fclean all
