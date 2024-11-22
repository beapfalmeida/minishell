/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:44:32 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/20 15:44:33 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_value(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/// @brief Checks if env is well-written and if it has args that aren't required.
/// @param tokens 
/// @param shell 
/// @return 0 if ok, 1 if fail.
static int	check_env(t_tokens *tokens, t_shell *shell)
{
	if (ft_strncmp(tokens->token, "env", 4) != 0)
	{
		do_error(0, tokens, shell, ERROR_CMD);
		return (1);
	}
	else if (tokens->next && tokens->next->type == ARG)
	{
		do_error(0, tokens->next, shell, OPEN_DF);
		return (1);
	}
	return (0);
}

/// @brief Prints the output of the env cmd.
/// @param shell 
/// @param tokens 
/// @return 
int	ft_env(t_shell *shell, t_tokens *tokens)
{
	char	**envp;
	char	*trim;

	if (check_env(tokens, shell))
		return (1);
	envp = shell->envp;
	while (*envp)
	{
		trim = ft_strtrim(*envp, "\"");
		if (has_value(trim))
			ft_printf_fd(STDOUT_FILENO, "%s\n", trim);
		free(trim);
		envp++;
	}
	return (1);
}
