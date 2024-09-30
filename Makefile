CC = cc
CFLAGS = -Wextra -Wall -Werror -g -I./includes

READLINE_PATH = vendor/readline/
RLFLAG = -L$(READLINE_PATH)/lib -lreadline

# flags used to suppress readline warnings in valgrind
VALFLAGS = --suppressions=readline.supp

NAME = minishell

LIBFT_DIR = includes/libft/
LIBFT_A = $(LIBFT_DIR)/libft.a

# Directories containing source files
SRC_DIR = src
EXECUTOR = executor handle_pwd handle_cd handle_echo handle_env handle_export
INIT = init
JSOBREIR = jsobreir-main

# Directory for obj files
OBJ_DIR = obj

# ------------------------------------------------------------------- #
# ------------------------------ Files ------------------------------ #
# ------------------------------------------------------------------- #

VPATHS =  	src/jsobreir/ \
			src/executor/ \
			src/executor/pwd \
			src/executor/cd \
			src/executor/echo \
			src/executor/env \
			src/executor/export \
			src/init/

SRC	=	$(addsuffix .c, $(EXECUTOR))\
		$(addsuffix .c, $(JSOBREIR))\
		$(addsuffix .c, $(INIT))

# Convert source files to object files in the obj directory
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# ------------------------------------------------------------------- #
# ------------------------------ Rules ------------------------------ #
# ------------------------------------------------------------------- #
vpath %.c $(VPATHS)

all: $(OBJ_DIR) $(LIBFT_A) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule for compiling source files to object files in obj/ directory
$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(RLFLAG) $(OBJ) $(LIBFT_A) -o $(NAME)

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
