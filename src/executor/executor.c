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

static void	handle_dir_file(t_tokens *tokens, t_shell *shell)
{
	char	*token;
	int		file;

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
		do_error(tokens, shell, OPEN_DF);
}

static void	reestablish_fds(t_shell *shell)
{
	dup2(shell->original_stdin, STDIN_FILENO);
	dup2(shell->original_stdout, STDOUT_FILENO);
	close(shell->original_stdin);
	close(shell->original_stdout);
}

static int	pipex(t_tokens *t, t_tokens *temp, t_shell *shell, t_pipe *p)
{
	p->i = -1;
	while (++p->i <= shell->n_pipes)
	{
		if (pipe(p->fd) == -1)
			return (perror(strerror(errno)), -1);
		p->pid[p->i] = fork();
		do_pipe(temp, shell, p);
		set_next_pipe(&temp);
	}
	wait_allchildren(t, shell, p->pid);
	return (0);
}

void	execute(t_tokens *tokens, t_shell *shell)
{
	t_tokens	*temp;
	t_pipe		p;
	int			pid[shell->n_pipes];//TODO: nao se pode fazer assim pela norminette

	shell->p = &p;
	temp = tokens;
	p.pid = pid;
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
	if (temp->type == DIR_FILE)
		return (handle_dir_file(temp, shell));
	if (shell->n_pipes)
	{
		if (pipex(tokens, temp, shell, &p) == -1)
			return ;
	}
	else
		exec_cmd(tokens, shell, 0);
	reestablish_fds(shell);
}
