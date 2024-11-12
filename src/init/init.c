#include "minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	char	**envp_array;
	int		i;

	envp_array = malloc((arr_len(envp) + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		envp_array[i] = ft_strdup(envp[i]);
		if (!envp_array[i])
			free_array(&envp_array[i], i);
		i++;
	}
	envp_array[i] = NULL;
	shell->envp = envp_array;
	shell->exit_code = 0;
	shell->last_path = ft_strdup(getenv("PWD"));
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
	if (shell->original_stdin == -1 || shell->original_stdout == -1)
		exit(EXIT_FAILURE);
	shell->interrupt_exec = false;
}

void	init_tokens(t_tokens *tokens)
{
	tokens->token = 0;
	tokens->type = 0;
	tokens->prev = NULL;
	tokens->next = NULL;
}

int	*init_fds(int *stop, t_tokens **infile)
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	*infile = NULL;
	*stop = 0;
	return (fd);
}
