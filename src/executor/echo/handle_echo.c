/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:44:26 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/23 15:51:08 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Cheks if the -n flag is used.
/// @param tokens 
/// @return 1 if -n is present, 0 if not.
static int	check_flag(t_tokens *tokens)
{
	char	*token;
	int		i;
	int		flag;

	i = 0;
	token = NULL;
	flag = 0;
	while (tokens && tokens->token
		&& !ft_strncmp(tokens->token, "-n", 2))
	{
		token = tokens->token;
		if (token[i++] == '-')
		{
			while (token[i] == 'n')
				i++;
			if (!token[i])
				flag++;
			else
				return (flag);
		}
		i = 0;
		tokens = tokens->next;
	}
	return (flag);
}

/// @brief Checks if the echo cmd is well-written.
/// @param tokens 
/// @param shell 
/// @return 
static int	check_echo(t_tokens *tokens, t_shell *shell)
{
	if (ft_strncmp(tokens->token, "echo", 5) != 0)
	{
		do_error(0, tokens, shell, ERROR_CMD);
		return (1);
	}
	if (!tokens->next)
	{
		ft_printf_fd(STDOUT_FILENO, "\n");
		return (1);
	}
	return (0);
}

/// @brief Prints the output of the echo command followed by arguments.
/// @param tokens 
/// @param shell 
/// @return 
int	ft_echo(t_tokens *tokens, t_shell *shell)
{
	t_tokens	*temp;
	int			flag;
	int			skip;

	temp = tokens->next;
	if (check_echo(tokens, shell))
		return (1);
	flag = check_flag(temp);
	skip = flag;
	while (flag--)
		temp = temp->next;
	if (skip && !(temp && temp->type == ARG))
		return (shell->exit_code = 0, 1);
	while (temp->token && temp->type == ARG)
	{
		ft_printf_fd(STDOUT_FILENO, temp->token);
		if (temp->next && temp->next->type == ARG)
			ft_printf_fd(STDOUT_FILENO, " ");
		temp = temp->next;
		if (temp == NULL)
			break ;
	}
	if (!skip)
		ft_printf_fd(STDOUT_FILENO, "\n");
	return (shell->exit_code = 0, 1);
}
