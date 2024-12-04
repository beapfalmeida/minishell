/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:44:10 by jsobreir          #+#    #+#             */
/*   Updated: 2024/12/04 14:15:11 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h> 
# include "./libft/libft.h"
# include "./libft/printf_fd/ft_printf_fd.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <errno.h>
# include <limits.h>

// From Google search about path size limits in Unix
# define MAX_PATH_SIZE 4096

// Signals
# define SIG_EXEC_BUILTIN 16
# define SIG_EXEC_FAILURE 10
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
# define ARG 14
# define DIR_FILE 13
# define SKIP 50
# define NOT_SKIP 42

// Built-ins
# define PWD 1
# define CD 2
# define ECHO 3
# define ENV 4
# define EXPORT 5
# define UNSET 6

extern int	g_signal;

typedef enum e_code
{
	ERROR_CMD,
	ERROR_CD,
	ERROR_2ARGS,
	ERROR_NDIR,
	IS_DIR,
	P_DENY,
	ERROR_FAR,
	ERROR_TILD,
	ERROR_OPEN,
	ERROR_OPENCMD,
	ERROR_SYNTAX,
	ERROR_N_VAL,
	ERROR_PIPE,
	ERROR_PDN,
	OPEN_DF,
	ERROR_UNCLP,
	ERROR_INVO,
}	t_error;

typedef struct s_fds
{
	int				in;
	int				out;
	int				pn;
	struct s_fds	*next;
}	t_fds;

typedef struct s_tokens
{
	char			*token;
	int				type;
	struct s_tokens	*next;
	struct s_tokens	*prev;
	bool			expanded;
}			t_tokens;

typedef struct s_pipe
{
	int			i;
	int			*pid;
	int			fd[2];
}	t_pipe;

typedef struct s_shell
{
	char	**envp;
	int		n_pipes;
	char	*last_path;
	int		original_stdin;
	int		original_stdout;
	int		exit_code;
	bool	interrupt_exec;
	t_fds	*fds;
	t_pipe	*p;
}	t_shell;

typedef struct s_split
{
	int		i;
	int		j;
	int		k;
	char	*s;
	char	**arr;
}	t_split;

typedef struct s_quotes
{
	bool	dq;
	bool	sq;
	bool	fe;
	int		i;
}	t_quotes;

// Init
void		init_tokens(t_tokens *token);
void		init_shell(t_shell *shell, char **envp);

// Parser
void		create_tokens(t_tokens **tokens, char *input);
void		redirect_in(t_tokens **temp);
void		redirect_out(t_tokens **temp);
void		append_out(t_tokens **temp);
void		append_in(t_tokens **temp);
void		command(t_tokens **temp);
int			is_symbol(char *token, int len);
void		loop_assigning(t_tokens **temp, int type);
int			assign_types(t_tokens **tokens);
int			check_dir_cmd(t_tokens **tokens);

// Expander
t_tokens	*handle_quotes(t_tokens *tokens, t_shell *shell);
t_tokens	*skip_redirects(t_tokens *tokens);
char		*handle_expander(char **envp, char *var, t_shell *shell);
char		*found_quote(t_tokens *tokens, char *token, t_quotes *q, int type);
char		*expand(char *token, t_shell *shell, t_quotes *q);
char		*process_token(char *token, t_tokens *tokens,
				t_shell *shell, t_quotes *q);
char		*get_var(char *token);
char		*skip_quote(char *token, char *quote_type, t_quotes *q);
void		init_quotes(t_quotes *q);

// Heredoc
int			find_limiter(t_tokens *tokens, t_shell *shell, int *fd);

// Create shell struct
int			process_tokens(t_tokens **tokens, t_shell *args);
int			get_input(t_tokens *temp, t_shell *shell, t_tokens *in, int *fd);
int			get_output(t_tokens *temp, t_shell *shell, int *fd);
int			*get_fds(t_tokens **tokens, t_shell *shell);
int			*init_fds(int *stop, t_tokens **infile);
int			open_file(t_tokens *tokens, t_shell *shell);

// Executor
int			exec_cmd(t_tokens *tokens, t_tokens **free, t_shell *shell, int ex);
char		**put_cmds(t_tokens	*token);
char		*get_path(char	*cmd, char **envp);
int			ft_isbuiltin(t_tokens *token);
int			ft_exec_builtin(t_tokens *token, t_shell *shell, int type_builtin);
void		execute(t_tokens **token, t_shell *shell);
void		handle_executable(t_tokens *tokens, t_shell *shell);
int			check_export(char *begin, t_tokens *tokens, t_shell *shell);
char		**order_alphabetically(char **envp);
void		print_export(char **envp);
void		update_env(char *begin, t_tokens *tokens, t_shell *shell);
void		add_var(char **env, t_tokens *tokens);
void		copy_envp(char **envp, char **new_envp, int i);
int			handle_dir_file(t_tokens **tokens, t_tokens *temp, t_shell *shell);

// Builtins
int			ft_pwd(t_tokens *token, t_shell *shell);
int			ft_cd(t_tokens *tokens, t_shell *shell);
int			ft_echo(t_tokens *token, t_shell *shell);
int			ft_env(t_shell *shell, t_tokens *tokens);
int			ft_export(t_tokens *token, t_shell *shell);
int			ft_unset(t_tokens *tokens, t_shell *shell);
void		add_envp_var(char **env, t_tokens *tokens, int i);

// Pipex
void		do_pipe(t_tokens *tokens, t_tokens **tofree,
				t_shell *shell, t_pipe *p);
void		set_next_pipe(t_tokens **temp);
void		wait_allchildren(t_tokens *tokens, t_shell *shell, int *pid);

// Free
void		free_all(t_tokens **tokens, t_shell *shell, char *input_buffer);
void		handle_null_input(t_fds *fds, t_tokens **tokens,
				t_shell *shell, t_pipe *p);
void		exec_fail(t_tokens **tokens, t_shell *shell,
				char **cmds, char *path);
void		free_fds(t_shell *shell);
void		clean_exit(t_tokens **tokens, t_shell *shell, t_pipe *p);

// Utils
t_tokens	*find_last(t_tokens *lst);
t_tokens	*new_node(char *content, int type);
void		add_back_list(t_tokens **lst, t_tokens *new);
void		lstclear(t_tokens **lst, int clean);
int			count_pipes(t_tokens **tokens);
char		**ft_arrdup(char **arr);
int			free_array(char	**arr, int len);
void		free_paths(char **paths);
int			arr_len(char **arr);
int			count_args(t_tokens *token);
int			ft_strclen(char *str, char c);
char		*ft_strfjoin(char *s1, char *s2, int _to_free);
long		getexitcode(t_tokens *tokens, char *number, int *flag);
int			is_file(char *file_name);
int			has_char(char *token, char c);
int			has_sintax_error(t_tokens *tokens, t_shell *shell);

void		add_back_fds(t_fds **lst, t_fds *new);
t_fds		*new_fds(int in, int out, int i);
t_fds		*find_last_fds(t_fds *lst);
t_fds		*find_redirects(t_fds *fds, int i);
int			check_exit_exec(t_tokens **tokens, t_shell *shell, char *inbuff);

// Split
char		**ft_split_adapted(char *s);
void		split_words(t_split *sp);
void		split_quotes(t_split *sp, char c);
int			ft_word_len(char *s, int i);
int			countwords(char *s, int i, int count);
int			count_inquote(char *s, int i);
int			find_quote(char *str);
int			malloc_gone_wrong(char **arr, int j);
int			check_nt(char *s);
void		write_char(t_split *sp);
void		split_quotes(t_split *sp, char c);

// Error handling
char		*get_error(t_error i);
void		do_error(char *begin, t_tokens *tokens, t_shell *shell,
				t_error error);
int			error_exit1(char *number, int i);
int			error_exit2(int overflow, long long ret, char *number);

//signals
void		signals(void);
void		handle_sigint(int sig);
void		signore(int sig);
void		child_signals(void);

#endif