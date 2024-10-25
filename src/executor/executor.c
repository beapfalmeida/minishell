#include "minishell.h"

/// @brief 
/// @param token 
/// @param shell 
/// @return 
int	ft_isbuiltin(t_tokens *token, t_shell *shell)
{
	if (ft_strncmp(token->token, "pwd", 3) == 0)
	{
		if (ft_pwd(token, shell) != 0)
			return (1);
	}
	else if (ft_strncmp(token->token, "cd", 2) == 0)
	{
		if ((ft_cd(token, shell) != 0))
			return (1);
	}
	else if (ft_strncmp(token->token, "echo", 4) == 0)
	{
		if ((ft_echo(token, shell) != 0))
			return (1);
	}
	else if (ft_strncmp(token->token, "env", 3) == 0)
	{
		if ((ft_env(shell, token) != 0))
			return (1);
	}
	else if (ft_strncmp(token->token, "export", 6) == 0)
	{
		if ((ft_export(token, shell) != 0))
			return (1);
	}
	else if (ft_strncmp(token->token, "unset", 6) == 0)
	{
		if ((ft_unset(token, shell) != 0))
			return (1);
	}
	else
		return (0);
	return (0);
}

/// @brief Function that executes a cmd.
/// @return 
int	exec_cmd(t_tokens *tokens, t_shell *shell)
{
	int		pid;
	int		status;
	char	*path;
	char	**cmds;

	if (ft_isbuiltin(tokens, shell))
		return (0); // Is a builtin
	else
	{
		pid = fork();
		if (pid < 0)
		{
			// TODO error when badfork
			return (1);
		}
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			cmds = put_cmds(tokens);
			if (!cmds)
				return (1);
			if (shell->fd_in != STDIN_FILENO)
			{
				dup2(shell->fd_in, STDIN_FILENO);
				close(shell->fd_in);
			}
			if (shell->fd_out != STDOUT_FILENO)
			{
				dup2(shell->fd_out, STDOUT_FILENO);
				close(shell->fd_out);
			}
			path = get_path(tokens->token, shell->envp);
			if (!path || execve(path, cmds, shell->envp) == -1)
			{
				child_cleanup(tokens, shell, 0);
				free_paths(cmds);
				if (path)
					free(path);
				exit(10);
			}
		}
		else
		{
			signal(SIGINT, signore);
			wait(&status);
			if (WIFEXITED(status))
				if (WEXITSTATUS(status) == 10)
					do_error(tokens, shell, ERROR_CMD);
		}
	}
	return (0);
}

static void	handle_dir_file(t_tokens *tokens, t_shell *shell)
{
	char *token;

	token = tokens->token;
	if (!strncmp(token, ".", ft_strlen(token)))
		do_error(tokens, shell, ERROR_FAR);
	else if (!strncmp(token, "~", ft_strlen(token)))
		do_error(tokens, shell, ERROR_TILD);
	else if (is_file(tokens->token) == 2)
		do_error(tokens, shell, IS_DIR);
	else if (is_file(tokens->token) == 1)
		do_error(tokens, shell, P_DENY);
	else if (!is_file(tokens->token))
		do_error(tokens, shell, ERROR_NSFD);
}

void	wait_allchildren(t_tokens *tokens, t_shell *shell, int *pid)
{
	int	i;
	int	status;

	i = -1;
	while (++i <= shell->n_pipes)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) == 10)
				do_error(tokens, shell, ERROR_CMD);
	}
}

static void	set_next_pipe(t_tokens **temp)
{
	while (*temp && (*temp)->type != PIPE)
		*temp = (*temp)->next;
	if (*temp)
		*temp = (*temp)->next;
}

void	execute(t_tokens *tokens, t_shell *shell)
{
	int			i;
	t_tokens	*temp;
	int			*pid;

	temp = tokens;
	if (temp->type == DIR_FILE)
		return (handle_dir_file(temp, shell));
	if (shell->n_pipes)
	{
		i = -1;
		pid = malloc((shell->n_pipes + 1) * sizeof(int));
		while (++i <= shell->n_pipes)
		{
			pid[i] = fork();
			do_pipe(temp, shell, i, pid);
			set_next_pipe(&temp);
		}
		wait_allchildren(tokens, shell, pid);
		dup2(shell->original_stdin, STDIN_FILENO);
	}
	else
		exec_cmd(tokens, shell);
}
