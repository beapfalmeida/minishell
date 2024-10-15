#include "minishell.h"

char	*get_error(t_error i)
{
	char	*str[6];

	str[0] = "bash: %s: Command not found\n";
	str[1] = "bash: %s: %s: No such file or directory\n";
	str[2] = "bash: %s: too many arguments\n";
	str[3] = "bash: %s: %s: Not a directory\n";
	str[4] = "bash: %s: Is a directory";
	str[5] = "bash: %s: Permission denied";
	return (str[i]);
}

void	do_error(t_tokens *tokens, t_shell *shell, t_error error)
{
	if (error == ERROR_OPEN || error == ERROR_NDIR)
		printf(get_error(error), tokens->token, tokens->next->token);
	else
		printf(get_error(error), tokens->token);
	if (error == ERROR_2ARGS || error == ERROR_NDIR  || error == ERROR_CMD)
		shell->exit_code = 1;
	else if (error == ERROR_OPEN)
		shell->exit_code = 127;
	else if (error == IS_DIR)
		shell->exit_code = 126;
}
