#include "minishell.h"

/// @brief 
/// @param token 
/// @param shell 
/// @return 
int	ft_isbuiltin(t_tokens *token)
{
	if (ft_strncmp(token->token, "pwd", 3) == 0)
		return (PWD);
	else if (ft_strncmp(token->token, "cd", 2) == 0)
		return (CD);
	else if (ft_strncmp(token->token, "echo", 4) == 0)
		return (ECHO);
	else if (ft_strncmp(token->token, "env", 3) == 0)
		return (ENV);
	else if (ft_strncmp(token->token, "export", 6) == 0)
		return (EXPORT);
	else if (ft_strncmp(token->token, "unset", 6) == 0)
		return (UNSET);
	else
		return (0);
}

int	ft_exec_builtin(t_tokens *token, t_shell *shell, int type_builtin)
{
	if (shell->fds->in < 0 && shell->n_pipes != 1)
		return (1);
	if (type_builtin == 0)
		return (0);
	if (type_builtin == PWD)
		return (ft_pwd(token, shell));
	else if (type_builtin == CD)
		return (ft_cd(token, shell));
	else if (type_builtin == ECHO)
		return (ft_echo(token, shell));
	else if (type_builtin == ENV)
		return (ft_env(shell, token));
	else if (type_builtin == EXPORT)
		return (ft_export(token, shell));
	else if (type_builtin == UNSET)
		return (ft_unset(token, shell));
	return (1);
}

/// @brief Function that executes a cmd.
/// @return 
int	exec_cmd(t_tokens *tokens, t_shell *shell, int executable)
{
	int		pid;
	int		status;
	char	*path;
	char	**cmds;

	if (shell->fds->in != STDIN_FILENO)
	{
		dup2(shell->fds->in, STDIN_FILENO);
		close(shell->fds->in);
	}
	if (shell->fds->out != STDOUT_FILENO)
	{
		dup2(shell->fds->out, STDOUT_FILENO);
		close(shell->fds->out);
	}
	if (ft_exec_builtin(tokens, shell, ft_isbuiltin(tokens)))
		return (1);
	else
	{
		pid = fork();
		if (pid < 0)
		{
			// TODO error when badfork
			return (1);
		}
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			cmds = put_cmds(tokens);
			if (!cmds)
				return (1);
			if (shell->fds->in < 0 || shell->fds->out < 0)
				exit(1);
			if (executable)
				handle_executable(tokens, shell);
			else
			{
				path = get_path(tokens->token, shell->envp);
				if (!path || execve(path, cmds, shell->envp) == -1)
				{
					free_all(tokens, shell, 0);
					free_paths(cmds);
					if (path)
						free(path);
					exit(SIG_EXEC_FAILURE);
				}
			}
		}
		else
		{
			signal(SIGINT, signore);
			wait(&status);
			if (WIFEXITED(status))
			{
				if (WEXITSTATUS(status) == 10)
					do_error(tokens, shell, ERROR_CMD);
				else
					shell->exit_code = WEXITSTATUS(status);				
			}
		}
	}
	return (0);
}

void	handle_executable(t_tokens *tokens, t_shell *shell)
{
	char *path;
	char    cwd[MAX_PATH_SIZE];
	char	*token;
	char	*dup;
	char	**args;

	token = tokens->token;
	getcwd(cwd, sizeof(cwd));
	dup = ft_strdup(&token[1]);
	path = ft_strjoin(cwd, dup);
	free(dup);
	args = malloc(sizeof(char *)* 2);
	args[0] = path;
	args[1] = NULL;
	if (!path || execve(path, args, shell->envp) == -1)
	{
		free(path);
		free(args);
	}
}

static void	handle_dir_file(t_tokens *tokens, t_shell *shell)
{
	char *token;
	int	file;

	token = tokens->token;
	file = is_file(tokens->token);
	if (!strncmp(token, ".", ft_strlen(token)))
		do_error(tokens, shell, ERROR_FAR);
	else if (!strncmp(token, "~", ft_strlen(token)))
		do_error(tokens, shell, ERROR_TILD);
	else if (file == 1)
		exec_cmd(tokens, shell, 1);
	else if (file == 2)
		do_error(tokens, shell, IS_DIR);
	else if (file == 4)
		do_error(tokens, shell, P_DENY);
	else if (!is_file(tokens->token))
		do_error(tokens, shell, ERROR_OPEN);
}

void	execute(t_tokens *tokens, t_shell *shell)
{
	t_tokens	*temp;
	t_pipe		p;
	int			pid[shell->n_pipes];

	shell->p = &p;
	temp = tokens;
	p.pid = pid;
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
	if (temp->type == DIR_FILE)
		return (handle_dir_file(temp, shell));
	if (shell->n_pipes)
	{
		p.i = -1;
		while (++p.i <= shell->n_pipes)
		{
			if (pipe(p.fd) == -1)
				;
			p.pid[p.i] = fork();
			do_pipe(temp, shell, &p);
			set_next_pipe(&temp);
		}
		wait_allchildren(tokens, shell, p.pid);
	}
	else
		exec_cmd(tokens, shell, 0);
	dup2(shell->original_stdin, STDIN_FILENO);
	dup2(shell->original_stdout, STDOUT_FILENO);
	close(shell->original_stdin);
	close(shell->original_stdout);
}
