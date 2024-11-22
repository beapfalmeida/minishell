/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:45:02 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/22 19:26:27 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handles tokens of executable type. Appends the name 
/// of the executable to the current dir pwd, got with getcwd.
/// @param tokens Pointer to the tokens struct.
/// @param shell Pointer to the shell vars struct.
void	handle_executable(t_tokens *tokens, t_shell *shell)
{
	char	*path;
	char	cwd[MAX_PATH_SIZE];
	char	*token;
	char	*dup;
	char	**args;

	token = tokens->token;
	getcwd(cwd, sizeof(cwd));
	dup = ft_strdup(&token[1]);
	path = ft_strjoin(cwd, dup);
	free(dup);
	args = malloc(sizeof(char *) * 2);
	args[0] = path;
	args[1] = NULL;
	if (!path || execve(path, args, shell->envp) == -1)
	{
		free(path);
		free(args);
	}
}

/// @brief Handles inputs corresponding to files or directoties.
/// @param tokens Pointer to the tokens struct.
/// @param temp Pointer to the tokens struct.
/// @param shell Pointer to the shell vars struct.
/// @return 1 in case of failure, 2 if executable, 3 is not executable
int	handle_dir_file(t_tokens **tokens, t_tokens *temp, t_shell *shell)
{
	char	*token;
	int		file;

	(void)tokens;
	token = temp->token;
	file = is_file(temp->token);
	if (!strncmp(token, ".", ft_strlen(token)))
		return(do_error(0, temp, shell, ERROR_FAR), 1);
	else if (!strncmp(token, "~", ft_strlen(token)))
		return(do_error(0, temp, shell, ERROR_TILD), 1);
	else if (file == 1 && *token != '/')
		return (2);
	else if (file == 1)
		return (3);
	else if (file == 2)
		return(do_error(0, temp, shell, IS_DIR), 1);
	else if (file == 4)
		return(do_error(0, temp, shell, P_DENY), 1);
	else if (!file)
		return(do_error(0, temp, shell, OPEN_DF), 1);
	return (1);
}

/// @brief Closes opened fds and reestablishes STDIN and STDOUT.
/// @param shell Pointer to the shell vars struct.
/// @param pid Array of pids for processes forked.
static void	reestablish_fds(t_shell *shell, int *pid)
{
	dup2(shell->original_stdin, STDIN_FILENO);
	dup2(shell->original_stdout, STDOUT_FILENO);
	close(shell->original_stdin);
	close(shell->original_stdout);
	if (pid)
		free(pid);
}

/// @brief Handles pipes.
/// @param t Pointer to the tokens struct.
/// @param temp Pointer to the tokens struct.
/// @param shell Pointer to the shell vars struct.
/// @param p Pointer to struct containing information about 
/// pipe processing in given token.
/// @return 
static int	pipex(t_tokens **t, t_tokens *temp, t_shell *shell, t_pipe *p)
{
	p->i = -1;
	while (++p->i <= shell->n_pipes)
	{
		if (pipe(p->fd) == -1)
			return (perror(strerror(errno)), free_all(t, shell, 0), -1);
		if (temp->type == CMD)
		{
			p->pid[p->i] = fork();
			do_pipe(temp, t, shell, p);
			set_next_pipe(&temp);
		}
		else
		{
			p->pid[p->i] = 0;
			set_next_pipe(&temp);
		}
	}
	wait_allchildren(*t, shell, p->pid);
	return (0);
}

/// @brief Execute a sequence of tokens.
/// @param tokens Pointer to the tokens struct.
/// @param shell Pointer to the shell vars struct.
void	execute(t_tokens **tokens, t_shell *shell)
{
	t_tokens	*temp;
	t_pipe		p;

	shell->p = &p;
	p.pid = 0;
	temp = *tokens;
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
	if (temp->type == DIR_FILE && !shell->n_pipes)
	{
		if (handle_dir_file(tokens, temp, shell) == 2)
			exec_cmd(temp, tokens, shell, 1);
		else
			exec_cmd(temp, tokens, shell, 0);
		reestablish_fds(shell, p.pid);
	}
	else if (shell->n_pipes)
	{
		p.pid = malloc((shell->n_pipes + 1) * sizeof(int));
		if (pipex(tokens, temp, shell, &p) == -1)
			return (reestablish_fds(shell, p.pid));
	}
	else
		exec_cmd(temp, tokens, shell, 0);
	reestablish_fds(shell, p.pid);
}
