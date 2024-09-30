CC = cc
CFLAGS = -Wextra -Wall -Werror -g -I./includes

READLINE_PATH = vendor/readline/
RLFLAG = -L$(READLINE_PATH)/lib -lreadline

NAME = minishell

LIBFT_DIR = includes/libft/
LIBFT_A = $(LIBFT_DIR)/libft.a
# Removed printf as the system's original function can be used

# Directories containing source files
SRC_DIR = src
EXECUTOR_DIR = $(SRC_DIR)/executor
PARSER_DIR = $(SRC_DIR)/parser
INIT_DIR = $(SRC_DIR)/init
PARSER_DIR = $(SRC_DIR)/parser
PRINTS_DIR = $(SRC_DIR)/prints
UTILS_DIR = $(SRC_DIR)/utils

# Directory for obj files
OBJ_DIR = obj

# ------------------------------------------------------------------- #
# ------------------------------ Files ------------------------------ #
# ------------------------------------------------------------------- #
SRC = $(SRC_DIR)/main.c \
      $(INIT_DIR)/init.c \
      $(EXECUTOR_DIR)/executor.c \
      $(EXECUTOR_DIR)/pwd/handle_pwd.c \
	  $(PARSER_DIR)/parser.c \
	  $(PARSER_DIR)/assign_types.c \
	  $(PARSER_DIR)/process_args.c \
	  $(PRINTS_DIR)/print.c \
	  $(UTILS_DIR)/utils.c \
	  $(UTILS_DIR)/split.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# ------------------------------------------------------------------- #
# ------------------------------ Rules ------------------------------ #
# ------------------------------------------------------------------- #
all: $(OBJ_DIR) $(LIBFT_A) $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(RLFLAG) $(OBJ) $(LIBFT_A) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(EXECUTOR_DIR)/pwd $(OBJ_DIR)/$(INIT_DIR) $(OBJ_DIR)/$(PARSER_DIR) $(OBJ_DIR)/$(PRINTS_DIR) $(OBJ_DIR)/$(UTILS_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all