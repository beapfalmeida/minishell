/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:44:22 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/22 13:40:14 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cd(t_tokens *token, t_shell *shell)
{
	if (ft_strncmp(token->token, "cd", 3) != 0)
	{
		do_error(0, token, shell, ERROR_CMD);
		return (1);
	}
	if (token->next && token->next->type == ARG
		&& token->next->next && token->next->next->type == ARG)
	{
		do_error(0, token, shell, ERROR_2ARGS);
		return (1);
	}
	if (token->next && is_file(token->next->token) == 1)
	{
		do_error(0, token, shell, ERROR_NDIR);
		return (1);
	}
	return (0);
}

int	ft_cd(t_tokens *tokens, t_shell *shell)
{
	char	*path;

	if (check_cd(tokens, shell) == 1)
		return (1);
	if (!tokens->next || !ft_strncmp(tokens->next->token, "~", 1))
	{
		path = ft_strdup(getenv("HOME"));
		if (tokens->next && !ft_strncmp(tokens->next->token, "~/", 2))
			path = ft_strfjoin(path, &tokens->next->token[1], 1);
		free(shell->last_path);
		shell->last_path = path;
	}
	else if (*tokens->next->token == '-')
		path = shell->last_path;
	else
	{
		path = tokens->next->token;
		free(shell->last_path);
		shell->last_path = ft_strdup(path);
	}
	if (chdir(path))
	{
		if (access(tokens->next->token, F_OK))
			return (do_error(0, tokens, shell, ERROR_OPENCMD), 1);
		return (do_error(0, tokens, shell, P_DENY), 1);
	}
	return (1);
}
