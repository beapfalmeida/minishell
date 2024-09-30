#include "minishell.h"

int	ft_env(t_shell *shell)
{
	char	**envp;

	envp = shell->envp;
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (0);
}
