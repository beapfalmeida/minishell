#include "minishell.h"

int	ft_cd(t_tokens *token)
{
	char	*path;
	char	*arg;

	arg = token->next;
	if (arg == '~' || arg == 'NULL')
		path = getent('HOME');
	if (chdir(path))
	{
		// Handle Error
		return (1);
	}
	return (0);
}