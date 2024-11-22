/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:44:26 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/20 15:44:27 by jsobreir         ###   ########.fr       */
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

	i = 0;
	token = NULL;
	if (tokens && tokens->token)
	{
		token = tokens->token;
		if (token[i++] == '-')
		{
			while (token[i] == 'n')
				i++;
			if (!token[i])
			{
				tokens = tokens->next;
				return (1);
			}
		}
	}
	return (0);
}

/// @brief Checks if the echo cmd is well-written.
/// @param tokens 
/// @param shell 
/// @return 
static int	check_echo(t_tokens *tokens, t_shell *shell)
{
	if (ft_strncmp(tokens->token, "echo", 4) != 0)
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

	temp = tokens;
	temp = temp->next;
	if (check_echo(tokens, shell))
		return (1);
	flag = check_flag(temp);
	if (flag)
		temp = temp->next;
	if (flag && !(temp && temp->type == ARG))
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
	if (!flag)
		ft_printf_fd(STDOUT_FILENO, "\n");
	return (shell->exit_code = 0, 1);
}
