#include "minishell.h"

void	free_fds(t_shell *shell)
{
	t_fds	*temp;

	while (shell->fds)
	{
		if (shell->fds->in != STDIN_FILENO)
			close(shell->fds->in);
		if (shell->fds->out != STDOUT_FILENO)
			close(shell->fds->out);
		temp = shell->fds;
		shell->fds = shell->fds->next;
		free(temp);
	}
}

void	free_all(t_tokens **tokens, t_shell *shell, char *input_buffer)
{
	if (shell->last_path)
		free(shell->last_path);
	if (shell->envp)
		free_paths(shell->envp);
	if (tokens)
		lstclear(tokens);
	if (STDIN_FILENO != shell->original_stdin)
		dup2(shell->original_stdin, STDIN_FILENO);
	if (STDOUT_FILENO != shell->original_stdout)
		dup2(shell->original_stdout, STDOUT_FILENO);
	if (shell->original_stdin != -1)
		close(shell->original_stdin);
	if (shell->original_stdout != -1)
		close(shell->original_stdout);
	free_fds(shell);
	if (input_buffer)
		free(input_buffer);
}

void	handle_null_input(t_fds *fds)
{
	int		fd_null;

	fd_null = 0;
	if (fds->in < 0)
	{
		fd_null = open("/dev/null", O_RDONLY);
		dup2(fd_null, STDIN_FILENO);
		close(fd_null);
		exit(EXIT_FAILURE);
	}
}

void	exec_fail(t_tokens **tokens, t_shell *shell, char **cmds, char *path)
{
	free_all(tokens, shell, 0);
	free_paths(cmds);
	if (path)
		free(path);
	exit(SIG_EXEC_FAILURE);
}
