#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h> 
# include "./libft/libft.h"
# include "./libft/ft_printf/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>

# define MAX_PATH_SIZE 4096 // From Google search about path size limits in Unix

typedef struct s_tokens
{
	char			*token;
	int				type;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}			t_tokens;


// Init
void	init_tokens(t_tokens *token);

// Parser

// Executor

// Builtins
int	ft_pwd(char *cwd);
int	exec_cmd(t_tokens *tokens);

// Free

// Utils

#endif