#include "minishell.h"

static int	ft_isbuiltin(t_tokens *token, t_shell *shell)
{
	if (ft_strncmp(token->token, "pwd", 4) == 0)
	{
		if (ft_pwd() != 0)
			return (1);
	}
	else if (ft_strncmp(token->token, "cd", 2) == 0)
	{
		if ((ft_cd(token) != 0))
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
	return (0);
}

/// @brief Function that executes a cmd.
/// @return 
int	exec_cmd(t_tokens *tokens, t_shell *shell)
{
	int	i;

	i = 0;
	if (ft_isbuiltin(tokens, shell) == 0)
		return (0); // Is a builtin
	// else
	// {
		// create_array(&tokens, shell);
		// get_path();
		// execve()
	// }
	return (0);
}

// char	*get_path()
// {
// 	char	*path;

// 	while ()
// 	return (path);
// }