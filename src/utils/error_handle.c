#include "minishell.h"

char	*get_error(t_error i)
{
	char	*str[16];

	str[0] = "%s: command not found\n";
	str[1] = "bash: cd: No such file or directory\n";
	str[2] = "bash: %s: too many arguments\n";
	str[3] = "bash: %s: %s: Not a directory\n";
	str[4] = "bash: %s: Is a directory\n";
	str[5] = "bash: %s: Permission denied\n";
	str[6] = "bash: .: filename argument required\n";
	str[7] = str[4];
	str[8] = "bash: %s: No such file or directory\n";
	str[9] = "%s: %s: No such file or directory\n";
	str[10] = "bash: syntax error near unexpected token `newline'\n";
	str[11] = "bash: %s: `%s': not a valid identifier\n";
	str[12] = "bash: syntax error near unexpected token `|'\n";
	str[13] = "bash: %s: Permission denied\n";
	str[14] = "bash: %s: No such file or directory\n";
	str[15] = "we dont handle unclosed pipes, sorry\n";
	return (str[i]);
}

void	do_error(char *begin, t_tokens *tokens, t_shell *shell, t_error error)
{
	if (error == ERROR_NDIR || error == ERROR_OPENCMD)
		ft_printf_fd(STDERR_FILENO,
			get_error(error), tokens->token, tokens->next->token);
	else if (error == ERROR_TILD)
		ft_printf_fd(STDERR_FILENO, get_error(IS_DIR), getenv("HOME"));
	else if (error == ERROR_N_VAL)
		ft_printf_fd(STDERR_FILENO,
			get_error(error), begin, tokens->token);
	else if (error == ERROR_SYNTAX || error == ERROR_PIPE)
		ft_printf_fd(STDERR_FILENO, "%s", get_error(error));
	else if (error == ERROR_UNCLP)
		ft_printf_fd(STDERR_FILENO, "%s", get_error(error));
	else
		ft_printf_fd(STDERR_FILENO, get_error(error), tokens->token);
	if (error == ERROR_2ARGS || error == ERROR_NDIR || error == ERROR_PDN
		|| error == ERROR_OPENCMD || error == ERROR_OPEN
		|| error == ERROR_N_VAL)
		shell->exit_code = 1;
	else if (error == ERROR_FAR || error == ERROR_SYNTAX)
		shell->exit_code = 2;
	else if (error == ERROR_CMD || error == OPEN_DF)
		shell->exit_code = 127;
	else if (error == IS_DIR || error == ERROR_TILD || error == P_DENY)
		shell->exit_code = 126;
}

int	error_quote(char *s, int i)
{
	if (!s[i])
	{
		printf("Sorry! Minishell doesn't handle unclosed quotes!\n");
		return (1);
	}
	return (0);
}

int	error_exit1(char *number, int i)
{
	if (!ft_isdigit(number[i]))
	{
		ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", number);
		return (1);
	}
	return (0);
}

int	error_exit2(int overflow, long long ret, char *number)
{
	if (overflow == 1 && ret != LONG_MIN)
	{
		ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", number);
		return (1);
	}
	return (0);
}
