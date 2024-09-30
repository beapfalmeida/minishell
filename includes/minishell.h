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

//token types
# define OUTPUT 1
# define CMD 2
# define PIPE 3
# define REDIRECT_IN 4
# define REDIRECT_OUT 5
# define INPUT 6
# define APPEND_IN 7
# define APPEND_OUT 8
# define LIMITER 9
# define ARG 10

typedef struct s_tokens
{
	char			*token;
	int				type;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}			t_tokens;

typedef struct s_shell
{
	char	**envp;
	int		fd_in;
	int		fd_out;
	char	***cmds;
	int		n_pipes;
}	t_shell;

// Init
void	init_tokens(t_tokens *token);

// Parser

// Executor
int	exec_cmd(t_tokens *tokens, t_shell *shell);

// Builtins
int	ft_pwd(void);
int	ft_cd(t_tokens *tokens);
int	ft_echo(t_tokens *token);
int	ft_env(t_shell *shell);
int	ft_export(t_tokens *token, t_shell *shell);

// Free

// Utils

#endif