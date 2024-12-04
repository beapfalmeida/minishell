/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:45:00 by jsobreir          #+#    #+#             */
/*   Updated: 2024/12/04 14:17:08 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent(t_tokens *tokens, t_shell *shell)
{
	int		status;

	signal(SIGINT, signore);
	wait(&status);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 10)
			do_error(0, tokens, shell, ERROR_CMD);
		else
			shell->exit_code = WEXITSTATUS(status);
	}
}

static int	prepare_fds(t_shell *shell)
{
	if (shell->fds->in < 0 || shell->fds->out < 0)
		return (1);
	if (shell->fds->in != STDIN_FILENO)
	{
		dup2(shell->fds->in, STDIN_FILENO);
		close(shell->fds->in);
	}
	if (shell->fds->out != STDOUT_FILENO)
	{
		dup2(shell->fds->out, STDOUT_FILENO);
		close(shell->fds->out);
	}
	return (0);
}

static int	execute_child(t_tokens *tokens, t_tokens **free,
	t_shell *shell, int exec)
{
	int		pid;
	char	*path;
	char	**cmds;

	pid = fork();
	if (pid < 0)
		return (perror(strerror(errno)), 1);
	if (pid == 0)
	{
		child_signals();
		cmds = put_cmds(tokens);
		if (!cmds)
			return (1);
		if (exec == 1)
			handle_executable(tokens, shell);
		else
		{
			path = get_path(tokens->token, shell->envp);
			if (!path || execve(path, cmds, shell->envp) == -1)
				exec_fail(free, shell, cmds, path);
		}
	}
	else
		parent(tokens, shell);
	return (0);
}

int	exec_cmd(t_tokens *tokens, t_tokens **free, t_shell *shell, int executable)
{
	if (prepare_fds(shell))
		return (1);
	if (ft_exec_builtin(tokens, shell, ft_isbuiltin(tokens)))
		return (1);
	else
	{
		if (execute_child(tokens, free, shell, executable))
			return (1);
	}
	if (shell->fds->in)
		close(shell->fds->in);
	return (0);
}
