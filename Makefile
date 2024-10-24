CC = cc
CFLAGS = -Wextra -Wall -Werror -g -I./includes

READLINE_PATH = vendor/readline/
RLFLAG = -L$(READLINE_PATH)/lib -lreadline

# flags used to suppress readline warnings in valgrind
VALFLAGS = --suppressions=readline.supp --leak-check=full

NAME = minishell

LIBFT_DIR = includes/libft/
LIBFT_A = $(LIBFT_DIR)/libft.a

# Directories containing source files
SRC_DIR = main
EXECUTOR = executor handle_pwd handle_cd handle_echo handle_env handle_export handle_unset pipex
INIT = init
PARSER = assign_types parser process_args skip_redirects expander heredoc
PRINTS = print
UTILS = utils utils2 utils3 split split_utils cmds error_handle
SIGNALS = signals

# Directory for obj files
OBJ_DIR = obj

# ------------------------------------------------------------------- #
# ------------------------------ Files ------------------------------ #
# ------------------------------------------------------------------- #

VPATHS =	src/				\
			src/executor/ 		\
			src/executor/pwd 	\
			src/executor/cd 	\
			src/executor/echo 	\
			src/executor/env 	\
			src/executor/export \
			src/executor/unset  \
			src/init/			\
			src/parser/			\
			src/prints/			\
			src/utils/			\
			src/signals			\

SRC	=	$(addsuffix .c, $(SRC_DIR))	\
		$(addsuffix .c, $(EXECUTOR))\
		$(addsuffix .c, $(INIT))	\
		$(addsuffix .c, $(PARSER))	\
		$(addsuffix .c, $(PRINTS))	\
		$(addsuffix .c, $(UTILS))	\
		$(addsuffix .c, $(SIGNALS))	\


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

valgrind: all
	valgrind $(VALFLAGS) ./minishell

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
