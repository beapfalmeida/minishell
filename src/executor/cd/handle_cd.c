#include "minishell.h"

static int	check_cd(t_tokens *token, t_shell *shell)
{
	if (ft_strncmp(token->token, "cd", 3) != 0)
	{
		do_error(token, shell, ERROR_CMD);
		return (1);
	}
	if (token->next && token->next->type == ARG &&
		token->next->next && token->next->next->type == ARG)
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
	if (!tokens->next)
	{
		path = getenv("HOME");
		shell->last_path = path;
	}
	else if (*tokens->next->token == '~')
	{
		path = getenv("HOME");
		shell->last_path = path;
	}
	else if (*tokens->next->token == '-')
	{
		path = shell->last_path;
	}
	else
	{
		path = tokens->next->token;
		shell->last_path = path;
	}
	if (chdir(path))
	{
		do_error(tokens, shell, ERROR_OPEN);
		return (1);
	}
	return (1);
}
