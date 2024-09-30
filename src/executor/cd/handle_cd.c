#include "minishell.h"

int	ft_cd(t_tokens *tokens)
{
	char	*path;
	char	*arg;

	if (tokens->next->type == ARG)
		arg = tokens->next->token;
	else
		arg = NULL;
	if (!ft_strncmp(arg, "~", 1) || !tokens->next->token)
		path = getenv("HOME");
	if (chdir(path))
	{
		// Handle Error
		return (1);
	}
	return (0);
}