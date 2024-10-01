#include "minishell.h"

static int	check_cd(t_tokens *token)
{
	if (token->next && token->next->type == ARG &&
		token->next->next && token->next->next->type == ARG)
	{
		// TODO cd: string not in pwd: obj
		return (1);
	}
	else if (ft_strncmp(token->token, "cd", 3) != 0)
	{
		// TODO zsh:command not found: name of cmd
		return (1);
	}
	return (0);
}

int	ft_cd(t_tokens *tokens, t_shell *shell)
{
	char	*path;

	if (check_cd(tokens) == 1)
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
		// Handle Error
		// TODO path doesnt exist
		return (1);
	}
	return (0);
}
