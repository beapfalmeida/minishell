/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:44:48 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/22 19:26:13 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check if pwd is well-written.
/// @param tokens 
/// @param shell 
/// @return 0 if ok, 1 if there's a mistake.
static int	check_pwd(t_tokens *tokens, t_shell *shell)
{
	if (ft_strncmp(tokens->token, "pwd", 4))
	{
		do_error(0, tokens, shell, ERROR_CMD);
		return (1);
	}
	return (0);
}

/// @brief Prints the result of the pwd cmd.
/// @return 
int	ft_pwd(t_tokens *token, t_shell *shell)
{
	char	cwd[MAX_PATH_SIZE];

	if (check_pwd(token, shell))
		return (1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	return (1);
}
