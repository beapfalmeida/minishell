#include "minishell.h"

char	*get_error(t_error i)
{
	char	*str[13];

	str[0] = "%s: Command not found\n";
	str[1] = "bash: cd: No such file or directory\n";
	str[2] = "bash: %s: too many arguments\n";
	str[3] = "bash: %s: %s: Not a directory\n";
	str[4] = "bash: %s: Is a directory\n";
	str[5] = "bash: %s: Permission denied\n";
	str[6] = "bash: .: filename argument required\n";
	str[7] = str[4];
	str[8] = "bash: %s: No such file or directory\n";
	str[9] = "bash: syntax error near unexpected token `newline'\n";
	str[10] = "bash: %s: No such file or directory\n";
	str[11] = "%s: %s: No such file or directory\n";
	str[12] = "bash: %s: `%s': not a valid identifier\n";
	return (str[i]);
}

void	do_error(t_tokens *tokens, t_shell *shell, t_error error)
{
	if (error == ERROR_NDIR || error == ERROR_OPENCMD)
		printf(get_error(error), tokens->token, tokens->next->token);
	else if (error == ERROR_TILD)
		printf(get_error(IS_DIR), getenv("HOME"));
	else if (error == ERROR_N_VAL)
		printf(get_error(error), tokens->token, tokens->next->token);
	else
		printf(get_error(error), tokens->token);
	if (error == ERROR_2ARGS || error == ERROR_NDIR || error == ERROR_OPENCMD)
		shell->exit_code = "1";
	else if (error == ERROR_FAR || error == ERROR_SYNTAX)
		shell->exit_code = "2";
	else if (error == ERROR_OPEN || error == ERROR_CMD)
		shell->exit_code = "127";
	else if (error == IS_DIR || error == ERROR_TILD)
		shell->exit_code = "126";
	else if (error == ERROR_N_VAL)
		shell->exit_code = "1";
}
