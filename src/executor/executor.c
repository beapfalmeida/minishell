#include "minishell.h"

void	handle_executable(t_tokens *tokens, t_shell *shell)
{
	char	*path;
	char	cwd[MAX_PATH_SIZE];
	char	*token;
	char	*dup;
	char	**args;

	token = tokens->token;
	getcwd(cwd, sizeof(cwd));
	dup = ft_strdup(&token[1]);
	path = ft_strjoin(cwd, dup);
	free(dup);
	args = malloc(sizeof(char *) * 2);
	args[0] = path;
	args[1] = NULL;
	if (!path || execve(path, args, shell->envp) == -1)
	{
		free(path);
		free(args);
	}
}

static void	handle_dir_file(t_tokens **tokens, t_tokens *temp, t_shell *shell)
{
	char	*token;
	int		file;

	token = temp->token;
	file = is_file(temp->token);
	if (!strncmp(token, ".", ft_strlen(token)))
		do_error(0, temp, shell, ERROR_FAR);
	else if (!strncmp(token, "~", ft_strlen(token)))
		do_error(0, temp, shell, ERROR_TILD);
	else if (file == 1 && *token != '/')
		exec_cmd(temp, tokens, shell, 1);
	else if (file == 1)
		exec_cmd(temp, tokens, shell, 0);
	else if (file == 2)
		do_error(0, temp, shell, IS_DIR);
	else if (file == 4)
		do_error(0, temp, shell, P_DENY);
	else if (!is_file((*tokens)->token))
		do_error(0, temp, shell, OPEN_DF);
}

static void	reestablish_fds(t_shell *shell, int *pid)
{
	dup2(shell->original_stdin, STDIN_FILENO);
	dup2(shell->original_stdout, STDOUT_FILENO);
	close(shell->original_stdin);
	close(shell->original_stdout);
	if (pid)
		free(pid);
}

static int	pipex(t_tokens **t, t_tokens *temp, t_shell *shell, t_pipe *p)
{
	p->i = -1;
	while (++p->i <= shell->n_pipes)
	{
		if (pipe(p->fd) == -1)
			return (perror(strerror(errno)), free_all(t, shell, 0), -1);
		p->pid[p->i] = fork();
		do_pipe(temp, t, shell, p);
		set_next_pipe(&temp);
	}
	wait_allchildren(*t, shell, p->pid);
	return (0);
}

void	execute(t_tokens **tokens, t_shell *shell)
{
	t_tokens	*temp;
	t_pipe		p;

	shell->p = &p;
	p.pid = 0;
	temp = *tokens;
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
	if (temp->type == DIR_FILE)
		return (handle_dir_file(tokens, temp, shell));
	if (shell->n_pipes)
	{
		p.pid = malloc((shell->n_pipes + 1) * sizeof(int));
		if (pipex(tokens, temp, shell, &p) == -1)
			return (reestablish_fds(shell, p.pid));
	}
	else
		exec_cmd(temp, tokens, shell, 0);
	reestablish_fds(shell, p.pid);
}
