#include "minishell.h"

static void	parent_process(int *new_fd)
{
 	dup2(new_fd[0], STDIN_FILENO);
	close(new_fd[0]);
	close(new_fd[1]);
}

static void	prepare_exec(t_tokens *tokens, t_shell *shell)
{
	int		res;
	char	**cmds;
	char	*path;

	cmds = put_cmds(tokens);
	res = ft_isbuiltin(tokens, shell);
	if (res)
	{
		free_paths(cmds);
		exit(0);
	}
	path = get_path(tokens->token, shell->envp);
	if (!path || execve(path, cmds, shell->envp) == -1)
	{
		free_paths(cmds);
		if (path)
			free(path);
		exit(10);
	}
	free_paths(cmds);
	free(path);
}

void	do_pipe(t_tokens *tokens, t_shell *shell, int i, int pid)
{
	int	fd[2];

	if (pipe(fd) == -1)
		;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (i == 0 && shell->fd_in != STDIN_FILENO)
			dup2(shell->fd_in, STDIN_FILENO);
		if (i == shell->n_pipes && shell->fd_out != STDOUT_FILENO)
			dup2(shell->fd_out, STDOUT_FILENO);
		else if (i != shell->n_pipes)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		prepare_exec(tokens, shell);
	}
	else
		signal(SIGINT, signore);
	parent_process(fd);
}
