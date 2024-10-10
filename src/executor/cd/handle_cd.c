#include "minishell.h"

static int	is_file(char *arg)
{
	int	fd;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (0);
	else
	{
		close(fd);
		return (1);
	}
}

static int	check_cd(t_tokens *token)
{
	if (token->next && token->next->type == ARG &&
		token->next->next && token->next->next->type == ARG)
	{
		printf(get_error(ERROR_2ARGS), token->token);
		return (1);
	}
	if (is_file(token->next->token))
	{
		printf(get_error(ERROR_NDIR), token->token);
		return (1);
	}
	else if (ft_strncmp(token->token, "cd", 3) != 0)
	{
		printf(get_error(ERROR_CMD), token->token);
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
		printf(get_error(ERROR_OPEN), tokens->token, path);
		return (0);
	}
	return (1);
}
