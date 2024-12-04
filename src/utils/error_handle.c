/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:46:05 by jsobreir          #+#    #+#             */
/*   Updated: 2024/12/04 14:18:01 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Error message selector.
/// @param i Number of the error message listed in t_error.
/// @return String containing the error message.
char	*get_error(t_error i)
{
	char	*str[17];

	str[0] = "%s: command not found\n";
	str[1] = "minishell: cd: No such file or directory\n";
	str[2] = "minishell: %s: too many arguments\n";
	str[3] = "minishell: %s: %s: Not a directory\n";
	str[4] = "minishell: %s: Is a directory\n";
	str[5] = "minishell: %s: Permission denied\n";
	str[6] = "minishell: .: filename argument required\n";
	str[7] = str[4];
	str[8] = "minishell: %s: No such file or directory\n";
	str[9] = "%s: %s: No such file or directory\n";
	str[10] = "minishell: syntax error near unexpected token `%s'\n";
	str[11] = "minishell: %s: `%s': not a valid identifier\n";
	str[12] = "minishell: syntax error near unexpected token `|'\n";
	str[13] = "minishell: %s: Permission denied\n";
	str[14] = "minishell: %s: No such file or directory\n";
	str[15] = "minishell: no support for pipe prompt\n";
	str[16] = "minishell: cd: %s: invalid option\n";
	return (str[i]);
}

static void	update_errorcode(t_shell *shell, t_error error)
{
	if (error == ERROR_2ARGS || error == ERROR_NDIR || error == ERROR_PDN
		|| error == ERROR_OPENCMD || error == ERROR_OPEN
		|| error == ERROR_N_VAL)
		shell->exit_code = 1;
	else if (error == ERROR_FAR || error == ERROR_SYNTAX || error == ERROR_INVO
		|| error == ERROR_SYNTAX || error == ERROR_PIPE)
		shell->exit_code = 2;
	else if (error == ERROR_CMD || error == OPEN_DF)
		shell->exit_code = 127;
	else if (error == IS_DIR || error == ERROR_TILD || error == P_DENY)
		shell->exit_code = 126;
}

/// @brief Prints error messages and changes current exit code.
/// @param begin Beggining of certain error messages.
/// @param tokens Pointer to the tokens struct.
/// @param shell Pointer to the shell vars struct.
/// @param error Error type.
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
	else if (error == ERROR_PIPE)
		ft_printf_fd(STDERR_FILENO, "%s", get_error(error));
	else if (error == ERROR_SYNTAX)
	{
		if (!tokens->next)
			ft_printf_fd(STDERR_FILENO, get_error(error), "newline");
		else
			ft_printf_fd(STDERR_FILENO, get_error(error), tokens->next->token);
	}
	else if (error == ERROR_UNCLP)
		ft_printf_fd(STDERR_FILENO, "%s", get_error(error));
	else
		ft_printf_fd(STDERR_FILENO, get_error(error), tokens->token);
	update_errorcode(shell, error);
}

// /// @brief Error message specific for unclosed brackets (minishell)
// /// @param s 
// /// @param i 
// /// @return 
// int	error_quote(char *s, int i)
// {
// 	if (!s[i])
// 	{
// 		printf("Sorry! Minishell doesn't handle unclosed quotes!\n");
// 		return (1);
// 	}
// 	return (0);
// }

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
	(void)ret;
	if (overflow == 1)
	{
		ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", number);
		return (1);
	}
	return (0);
}
