#include "minishell.h"

static int has_value(char *env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static int	check_env(t_tokens *tokens, t_shell *shell)
{
	if (ft_strncmp(tokens->token, "env", 4) != 0)
	{
		do_error(tokens, shell, ERROR_CMD);
		return (1);
	}
	else if (tokens->next && tokens->next->type == ARG)
	{
		do_error(tokens, shell, ERROR_2ARGS);
		return (1);
	}
	return (0);
}

int	ft_env(t_shell *shell, t_tokens *tokens)
{
	char	**envp;

	if (check_env(tokens, shell))
		return (1);
	envp = shell->envp;
	while (*envp)
	{
		if (has_value(*envp))
			printf("%s\n", *envp);
		envp++;
	}
	return (1);
}
