#include "minishell.h"

static int	check_env(t_tokens *token)
{
	if (token->next && token->next->type == ARG)
	{
		printf(get_error(ERROR_2ARGS), token->token);
		return (1);
	}
	else if (ft_strncmp(token->token, "env", 4) != 0)
	{
		printf(get_error(ERROR_CMD), token->token);
		return (1);
	}
	return (0);
}

int	ft_env(t_shell *shell, t_tokens *tokens)
{
	char	**envp;

	if (check_env(tokens))
		return (1);
	envp = shell->envp;
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (1);
}
