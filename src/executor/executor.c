#include "minishell.h"

/// @brief Function that executes a cmd.
/// @return 
int	exec_cmd(t_tokens *tokens)
{
	// if cmd found
	// Execve with flags

	// Find Builtins
	if (ft_strncmp(tokens->token, "pwd", 4) == 0)
		if (ft_pwd(tokens->token) != 0)
			return (1);
	return (0);
	// Wrong Command
}