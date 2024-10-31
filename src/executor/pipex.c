#include "minishell.h"

void	wait_allchildren(t_tokens *tokens, t_shell *shell, int *pid)
{
	int	i;
	int	status;
	t_tokens *temp;

	i = -1;
	temp = tokens;
	while (++i <= shell->n_pipes)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 10)
				do_error(temp, shell, ERROR_CMD);
			else
				shell->exit_code = 0;
		}
		set_next_pipe(&temp);
	}
}

void	set_next_pipe(t_tokens **temp)
{
	while (*temp && (*temp)->type != PIPE)
		*temp = (*temp)->next;
	if (*temp && (*temp)->next)
		*temp = (*temp)->next;
}

static void	parent_process(int *new_fd)
{
 	// char *buffer = NULL;
	// if (read(STDIN_FILENO, buffer, 1) == 0)
		dup2(new_fd[0], STDIN_FILENO);
	// else
	// 	dup2(shell->original_stdin, STDIN_FILENO);
	close(new_fd[0]);
	close(new_fd[1]);
}

static void	prepare_exec(t_tokens *tokens, t_shell *shell, t_pipe *p)
{
	int		res;
	char	**cmds;
	char	*path;

	cmds = put_cmds(tokens);
	res = ft_isbuiltin(tokens, shell); // Pq esta verificacao aqui?
	if (res)
	{
		free_all(tokens, shell, 0);
		free_paths(cmds);
		exit(0);
	}
	close(p->fd[1]);
	close(p->fd[0]);
	path = get_path(tokens->token, shell->envp);
	if (!path || execve(path, cmds, shell->envp) == -1)
	{
		free_all(tokens, shell, 0);
		free_paths(cmds);
		if (path)
			free(path);
		exit(10);
	}
}

static t_fds	*find_redirects(t_fds *fds, int i)
{
	t_fds *temp;

	temp = fds;
	while (temp)
	{
		if (i == temp->pn)
			return (temp);
		temp = temp->next;
	}
	return (fds);
}

void	do_pipe(t_tokens *tokens, t_shell *shell, t_pipe *p)
{
	t_fds	*fds;
	if (p->pid[p->i] == 0)
	{
		signal(SIGINT, SIG_DFL); //TODO: dar mute aos outros sinais tambem
		if (p->i == 0 && shell->fd_in != STDIN_FILENO)
			dup2(shell->fd_in, STDIN_FILENO);
		fds = find_redirects(shell->fds, p->i);
		if (fds->pn == p->i && fds->fd != STDOUT_FILENO)
			dup2(fds->fd, STDOUT_FILENO);
		else if (p->i != shell->n_pipes)
			dup2(p->fd[1], STDOUT_FILENO);
		prepare_exec(tokens, shell, p);
	}
	else
		signal(SIGINT, signore);
	parent_process(p->fd);
}
