#include "minishell.h"

static int	check_cd(t_tokens *token, t_shell *shell)
{
	if (ft_strncmp(token->token, "cd", 3) != 0)
	{
		do_error(token, shell, ERROR_CMD);
		return (1);
	}
	if (token->next && token->next->type == ARG
		&& token->next->next && token->next->next->type == ARG)
	{
		do_error(token, shell, ERROR_2ARGS);
		return (1);
	}
	if (token->next && is_file(token->next->token) == 1)
	{
		do_error(token, shell, ERROR_NDIR);
		return (1);
	}
	return (0);
}

int	ft_cd(t_tokens *tokens, t_shell *shell)
{
	char	*path;

	if (check_cd(tokens, shell) == 1)
		return (1);
	if (!tokens->next || *tokens->next->token == '~')
	{
		path = getenv("HOME");
		free(shell->last_path);
		shell->last_path = ft_strdup(path);
	}
	else if (*tokens->next->token == '-')
		path = shell->last_path;
	else
	{
		path = tokens->next->token;
		free(shell->last_path);
		shell->last_path = ft_strdup(path);
	}
	if (chdir(path))
	{
		if (access(tokens->next->token, F_OK))
			return (do_error(tokens, shell, ERROR_OPENCMD), 1);
		return (do_error(tokens, shell, P_DENY), 1);
	}
	return (1);
}
