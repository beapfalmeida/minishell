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
	if (shell->fd_in)
		close(shell->fd_in);
	if (shell->fd_out)
		close(shell->fd_out);
	if (input_buffer)
		free(input_buffer);
	// if (shell->p && shell->p->fd[1])
	// 	close(shell->p->fd[1]);
	// if (shell->p && shell->p->fd[0])
	// 	close(shell->p->fd[0]);
}
