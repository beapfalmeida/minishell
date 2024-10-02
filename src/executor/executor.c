#include "minishell.h"

/// @brief 
/// @param paths 
void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		i++;
	while (i--)
		free(paths[i]);
	free(paths);
}

/// @brief 
/// @param token 
/// @param shell 
/// @return 
static int	ft_isbuiltin(t_tokens *token, t_shell *shell)
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
		if ((ft_env(shell) != 0))
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
		return (1);
	return (0);
}

/// @brief Function that executes a cmd.
/// @return 
int	exec_cmd(t_tokens *tokens, t_shell *shell)
{
	int		pid;
	char	*path;
	char	**cmds;

	if (ft_isbuiltin(tokens, shell) == 0)
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
			path = get_path(tokens->token, shell->envp);
			if (!path)
				return (free_array(cmds, arr_len(cmds)), 1);
			if (execve(path, cmds, shell->envp) == -1)
			{
				// TODO return error and clean exit
				return (1);
			}
		}
		else
			wait(NULL);
	}
	return (0);
}
