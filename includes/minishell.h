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
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>

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

// # define STDIN STDIN_FILENO
// # define STDOUT STDOUT_FILENO

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
	int		n_pipes;
	char	*last_path;
	int		original_stdin;
	int		original_stdout;
}	t_shell;

typedef struct split
{
	int	i;
	int	j;
	int	k;
	char	*s;
	char	**arr;
}	t_split;

// Init
void		init_tokens(t_tokens *token);

// Parser
void		create_tokens(t_tokens **tokens, char *input);
void		redirect_in(t_tokens **temp);
void		redirect_out(t_tokens **temp);
void		append_out(t_tokens **temp);
void		append_in(t_tokens **temp);
void		command(t_tokens **temp);
int			is_symbol(char *token);
void		loop_assigning(t_tokens **temp, int type);
void		assign_types(t_tokens **tokens);
char 		*find_expander2(char	*token, char **envp);
t_tokens	*handle_quotes(t_tokens *tokens, t_shell *shell);

// Create shell struct
void		process_tokens(t_tokens **tokens, t_shell *args);
int			get_input(t_tokens **tokens);
int			get_output(t_tokens **tokens);

// Executor

int			exec_cmd(t_tokens *tokens, t_shell *shell);
char		**put_cmds(t_tokens	*token);
char		*get_path(char	*cmd, char **envp);
int			ft_isbuiltin(t_tokens *token, t_shell *shell);
void		execute(t_tokens *token, t_shell *shell);
t_tokens	*skip_redirects(t_tokens *tokens);

// Builtins
int			ft_pwd(t_tokens *token);
int			ft_cd(t_tokens *tokens, t_shell *shell);
int			ft_echo(t_tokens *token);
int			ft_env(t_shell *shell);
int			ft_export(t_tokens *token, t_shell *shell);
int			ft_unset(t_tokens *tokens, t_shell *shell);
void		find_expander(t_tokens	*tokens, char **envp);
char		*handle_expander(char **envp, char *var);

// Free

// Utils
t_tokens	*find_last(t_tokens *lst);
t_tokens	*new_node(char *content);
void		add_back_list(t_tokens **lst, t_tokens *new);
void		lstclear(t_tokens **lst);
int			count_pipes(t_tokens **tokens);

int			free_array(char	**arr, int	len);
void		free_paths(char **paths);
int			arr_len(char **arr);
int			count_args(t_tokens *token);
int			ft_strclen(char *str, char c);

// Split
char		**ft_split_adapted(char *s);
void		split_words(t_split *sp);
void		put_word(t_split *sp, int c);
void		split_quotes(t_split *sp, char c);
int			ft_word_len(char *s, int i);
int			countwords(char *s, int i, int count);
int			count_inquote(char *s, int i);
int			find_quote(char *str);

// testing
void		print_tokens(t_tokens **begin_list);
void		print_arr(char **arr);

void		badopen(int fd, char *file);
void		do_pipe(t_tokens *tokens, t_shell *shell, int i);

#endif