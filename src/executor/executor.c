#include "minishell.h"


/// @brief 
/// @param token 
/// @param shell 
/// @return 
int	ft_isbuiltin(t_tokens *token, t_shell *shell)
{
	if (ft_strncmp(token->token, "pwd", 4) == 0)
	{
		if (ft_pwd(token) != 0)
			return (1);
	}
	else if (ft_strncmp(token->token, "cd", 2) == 0)
	{
		if ((ft_cd(token, shell) != 0))
			return (1);
	}
	else if (ft_strncmp(token->token, "echo", 4) == 0)
	{
		if ((ft_echo(token) != 0))
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
			if (execve(path, cmds, shell->envp) == -1)
			{
				printf(get_error(ERROR_CMD), tokens->token);
				//TODO: free ?
			}
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}

void	execute(t_tokens *tokens, t_shell *shell)
{
	int		i;
	t_tokens	*temp;

	temp = tokens;
	if (shell->n_pipes)
	{
		i = -1;
		while (++i <= shell->n_pipes)
		{
			do_pipe(temp, shell, i);
			while (temp && temp->type != PIPE)
				temp = temp->next;
			if (temp)
				temp = temp->next;
		}
		dup2(shell->original_stdin, STDIN_FILENO);
	}
	else
		exec_cmd(tokens, shell);
}

t_tokens	*skip_redirects(t_tokens *tokens)
{
	t_tokens	*new_tokens;

	new_tokens = NULL;
	while (tokens && tokens->token)
	{
		if (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT)
		{
			tokens = tokens->next;
			if (tokens->type == INPUT || tokens->type == OUTPUT)
				tokens = tokens->next;
		}
		if (tokens && tokens->token)
		{
			add_back_list(&new_tokens, new_node(tokens->token));
			tokens = tokens->next;
		}
	}
	assign_types(&new_tokens);
	return (new_tokens);
}
