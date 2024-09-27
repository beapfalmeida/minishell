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
	//else
	//	execute();
	return (0);
	// Wrong Command
}

void	execute(char *path, char **args, char **envp)
{
	if (execve(path, args, envp) == -1)
	{
		perror(strerror(errno));
		free_data(path, args);
		exit(1);
	}
}