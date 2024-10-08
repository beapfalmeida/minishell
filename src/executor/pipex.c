#include "minishell.h"

static void	parent_process(int pid, int *new_fd)
{
	(void)pid;
	(void)new_fd;
 	dup2(new_fd[0], STDIN_FILENO);
	close(new_fd[0]);
	close(new_fd[1]);
}

static void	prepare_exec(t_tokens *tokens, t_shell *shell)
{
	int	res;
	char **cmds;

	cmds = put_cmds(tokens);
	res = ft_isbuiltin(tokens, shell);
	if (res)
	{
		free_array(cmds, arr_len(cmds));
		exit(0);
	}
	if (execve(get_path(tokens->token, shell->envp), cmds, NULL) == -1)
		perror("error execve");
}

void	do_pipe(t_tokens *tokens, t_shell *shell, int i)
{
	int	pid = 0;
	int	fd[2];

	if (pipe(fd) == -1)
		;
	pid = fork();
	if (pid == 0)
	{
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
	parent_process(pid, fd);
	waitpid(pid, NULL, 0);
}
