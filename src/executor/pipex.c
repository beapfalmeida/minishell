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
			if (WEXITSTATUS(status) == SIG_EXEC_FAILURE)
				do_error(temp, shell, ERROR_CMD);
			else if (WEXITSTATUS(status) == 15)
				do_error(tokens, shell, ERROR_OPEN);
			else
				shell->exit_code = WEXITSTATUS(status);
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

static void	parent_process(t_tokens *tokens, t_shell *shell, t_pipe *p)
{
	(void)shell;
	(void)tokens;
	dup2(p->fd[0], STDIN_FILENO);
	close(p->fd[0]);
	close(p->fd[1]);
}

static void	prepare_exec(t_tokens *tokens, t_shell *shell, t_pipe *p)
{
	int		res;
	char	**cmds;
	char	*path;

	(void)p;
	cmds = put_cmds(tokens);
	res = ft_isbuiltin(tokens);
	if (res)
	{
		ft_exec_builtin(tokens, shell, ft_isbuiltin(tokens));
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
		exit(SIG_EXEC_FAILURE);
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
	int		fd_null;

	fd_null = 0;
	if (p->pid[p->i] == 0)
	{
		signal(SIGINT, SIG_DFL); //TODO: dar mute aos outros sinais tambem
		fds = find_redirects(shell->fds, p->i);
		if (fds->in < 0)
		{
			fd_null = open("/dev/null", O_RDONLY);
			dup2(fd_null, STDIN_FILENO);
			close(fd_null);
			exit(EXIT_FAILURE);
		}
		if (fds->out == -1)
			exit(1);
		else if (p->i == fds->pn && fds->in != STDIN_FILENO)
			dup2(fds->in, STDIN_FILENO);
		if (fds->pn == p->i && fds->out != STDOUT_FILENO)
			dup2(fds->out, STDOUT_FILENO);
		else if (p->i != shell->n_pipes)
			dup2(p->fd[1], STDOUT_FILENO);
		prepare_exec(tokens, shell, p);
	}
	else
		signal(SIGINT, signore);
	parent_process(tokens, shell, p);
}
