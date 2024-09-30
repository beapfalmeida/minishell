#include "minishell.h"

int	ft_cd(t_tokens *tokens)
{
	char	*path;
	char	*arg;

	if (tokens->next && tokens->next->type == ARG)
	{
		arg = tokens->next->token;
		path = arg;
	}
	else
	{
		arg = NULL;
		path = getenv("HOME");
	}
	if (arg && !tokens->next->token) 
		path = getenv("HOME");
	if (chdir(path))
	{
		// Handle Error
		return (1);
	}
	return (0);
}