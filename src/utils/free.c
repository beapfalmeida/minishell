#include "minishell.h"

void	free_all(t_tokens *tokens, t_shell *shell, char *input_buffer)
{
	if (shell->last_path)
		free(shell->last_path);
	if (shell->envp)
		free_paths(shell->envp);
	if (tokens)
		lstclear(&tokens);
	if (shell->original_stdin)
		close(shell->original_stdin);
	if (shell->original_stdout)
		close(shell->original_stdout);
	if (shell->fds_in->fd)
		close(shell->fds_in->fd);
	if (shell->fds_out->fd)
		close(shell->fds_out->fd);
	if (input_buffer)
		free(input_buffer);
	// if (shell->p && shell->p->fd[1])
	// 	close(shell->p->fd[1]);
	// if (shell->p && shell->p->fd[0])
	// 	close(shell->p->fd[0]);
}
