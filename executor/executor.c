#include "minishell.h"

/// @brief Function that executes a cmd.
/// @return 
int	exec_cmd(t_tokens *tokens)
{

	// if cmd found
	// Execve with flags

	// Find Builtins
	if (ft_strncmp(tokens->token, "pwd", 3))
		if (!ft_pwd(tokens->token))
			
	// Wrong Command
}