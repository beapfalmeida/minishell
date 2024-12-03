CC = cc
CFLAGS = -Wextra -Wall -Werror -g -I./includes

READLINE_PATH = vendor/readline/
RLFLAG = -L$(READLINE_PATH)/lib -lreadline

# flags used to suppress readline warnings in valgrind
VALFLAGS = -s --suppressions=readline.supp --tool=memcheck -q --leak-check=full

NAME = minishell

LIBFT_DIR = includes/libft/
LIBFT_A = $(LIBFT_DIR)/libft.a

# Directories containing source files
SRC_DIR = main
EXECUTOR = executor handle_pwd handle_cd handle_echo handle_env handle_export exp_utils handle_unset pipex exec_cmd builtins exp_utils_2
INIT = init
PARSER = assign_types assign_types2 parser process_args skip_redirects expander expander2 heredoc redirects
UTILS = utils utils2 utils3 utils4 split split_utils split_utils2 cmds error_handle free
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
			src/utils/			\
			src/signals			\

SRC	=	$(addsuffix .c, $(SRC_DIR))	\
		$(addsuffix .c, $(EXECUTOR))\
		$(addsuffix .c, $(INIT))	\
		$(addsuffix .c, $(PARSER))	\
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