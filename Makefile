CC = cc
CFLAGS = -Wextra -Wall -Werror -g -I./includes

READLINE_PATH = vendor/readline/
RLFLAG = -L$(READLINE_PATH)/lib -lreadline

# flags used to supress readline warnings in valgrind
VALFLAGS = --suppressions=readline.supp

NAME = minishell

LIBFT_DIR = includes/libft/
LIBFT_A = $(LIBFT_DIR)/libft.a
# Removed printf as the system's original function can be used

# Directories containing source files
SRC_DIR = src
EXECUTOR_DIR = $(SRC_DIR)/executor
PARSER_DIR = $(SRC_DIR)/parser
INIT_DIR = $(SRC_DIR)/init
JSOBREIR_DIR = jsobreir

# Directory for obj files
OBJ_DIR = obj

# ------------------------------------------------------------------- #
# ------------------------------ Files ------------------------------ #
# ------------------------------------------------------------------- #
SRC = $(JSOBREIR_DIR)/jsobreir-main.c \
		$(INIT_DIR)/init.c \
		$(EXECUTOR_DIR)/executor.c \
		$(EXECUTOR_DIR)/pwd/handle_pwd.c \
		$(EXECUTOR_DIR)/cd/handle_cd.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# ------------------------------------------------------------------- #
# ------------------------------ Rules ------------------------------ #
# ------------------------------------------------------------------- #
all: $(OBJ_DIR) $(LIBFT_A) $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(RLFLAG) $(OBJ) $(LIBFT_A) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(JSOBREIR_DIR) $(OBJ_DIR)/$(EXECUTOR_DIR)/pwd $(OBJ_DIR)/$(INIT_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

valgrind:
	valgrind $(VALFLAGS) ./minishell

clean:
	rm -f $(OBJ)
	@if [ -d "$(LIBFT_DIR)" ]; then \
	$(MAKE) -C $(LIBFT_DIR) clean; \
	fi

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	@if [ -d "$(LIBFT_DIR)" ]; then \
	$(MAKE) -C $(LIBFT_DIR) fclean; \
	fi

re: fclean all