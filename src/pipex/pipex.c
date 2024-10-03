#include "minishell.h"

static void	parent_process(int pid, int *new_fd)
{
	(void)pid;
	dup2(new_fd[0], STDIN_FILENO);
	close(new_fd[0]);
	close(new_fd[1]);
}

static void	do_pipe(t_tokens *tokens, t_shell *shell, int i)
{
	int	new_fd[2];
	int	pid;
	int	res;

	if (pipe(new_fd) == -1)
		; //TODO: Error pipe
	pid = fork();
	if (pid < 0)
		; //TODO: Error fork
	if (pid == 0)
	{
		if (i == 0 && shell->fd_in != STDIN_FILENO)
			dup2(shell->fd_in, STDIN_FILENO);
		if (i == shell->n_pipes && shell->fd_out != STDOUT_FILENO)
			dup2(shell->fd_out, STDOUT_FILENO);
		else //TODO: nao sei se isto funciona bem, ver depois
			dup2(new_fd[1], STDOUT_FILENO);
		close(new_fd[0]);
		close(new_fd[1]);
		res = ft_isbuiltin(tokens, shell);
		if (res)
			exit(0);
		else if (execve(get_path(shell->cmds[i][0], shell->envp), shell->cmds[i], NULL) == -1)
			printf("Command not found: %s", shell->cmds[i][0]);
	}
	else
		parent_process(pid, new_fd);
}

void	execute(t_tokens *tokens, t_shell *shell)
{
	int		i;
	if (shell->n_pipes)
	{
		i = -1;
		while (++i < shell->n_pipes)
		{
			do_pipe(tokens, shell, i);
			while (tokens && tokens->type != PIPE)
				tokens = tokens->next;
			tokens = tokens->next;
		}
		waitpid(0, NULL, 0);
	}
	else
		exec_cmd(tokens, shell);
}
