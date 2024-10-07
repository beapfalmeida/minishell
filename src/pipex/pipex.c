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
	char **cmds;

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
		cmds = put_cmds(tokens);
		res = ft_isbuiltin(tokens, shell);
		if (res)
		{
			exit(0);
			free_array(cmds, arr_len(cmds));
		}
		else if (execve(get_path(tokens->token, shell->envp), cmds, NULL) == -1)
			;
	}
	else
		parent_process(pid, new_fd);
}

void	execute(t_tokens *tokens, t_shell *shell)
{
	int		i;
	t_tokens	*temp;

	temp = tokens;
	if (shell->n_pipes)
	{
		i = -1;
		while (++i < shell->n_pipes)
		{
			do_pipe(temp, shell, i);
			while (temp && temp->type != PIPE)
				temp = temp->next;
			if (temp)
				temp = temp->next;
		}
		waitpid(0, NULL, 0);
	}
	else
		exec_cmd(tokens, shell);
}
