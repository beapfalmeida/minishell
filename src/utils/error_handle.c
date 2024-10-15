#include "minishell.h"

char	*get_error(t_error i)
{
	char	*str[4];

	str[0] = "%s: Command not found\n";
	str[1] = "bash: %s: %s: No such file or directory\n";
	str[2] = "bash: %s: too many arguments\n";
	str[3] = "bash: %s: Makefile: Not a directory\n";
	return (str[i]);
}

void	do_error(t_tokens *tokens, t_shell *shell, t_error error)
{
	if (error == ERROR_OPEN)
		printf(get_error(error), tokens->token, tokens->next->token);
	else
		printf(get_error(error), tokens->token);
	if (error == ERROR_2ARGS || error == ERROR_NDIR  || error == ERROR_CMD)
		shell->exit_code = 1;
	else if (error == ERROR_OPEN)
		shell->exit_code = 127;
}
