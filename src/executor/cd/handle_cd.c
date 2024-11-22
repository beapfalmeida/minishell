/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:44:22 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/22 16:01:53 by jsobreir         ###   ########.fr       */
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

static int	do_cd(char *path, t_tokens *tokens, t_shell *shell)
{
	char	cwd[MAX_PATH_SIZE];

	free(shell->last_path);
	getcwd(cwd, sizeof(cwd));
	shell->last_path = ft_strdup(cwd);
	if (chdir(path))
	{
		free(path);
		if (access(tokens->next->token, F_OK))
			return (do_error(0, tokens, shell, ERROR_OPENCMD), 1);
		return (do_error(0, tokens, shell, P_DENY), 1);
	}
	free(path);
	return (1);
}

int	ft_cd(t_tokens *tokens, t_shell *shell)
{
	char	*path;
	int		flag;

	flag = 0;
	if (check_cd(tokens, shell) == 1)
		return (1);
	if (!tokens->next || !ft_strncmp(tokens->next->token, "~", 1))
	{
		path = ft_strdup(getenv("HOME"));
		if (tokens->next && !ft_strncmp(tokens->next->token, "~/", 2))
			path = ft_strfjoin(path, &tokens->next->token[1], 1);
	}
	else if (*tokens->next->token == '-')
	{
		flag = 1;
		path = ft_strdup(shell->last_path);
	}
	else if (is_file(tokens->next->token) == 2)
		path = ft_strdup(tokens->next->token);
	else
		path = tokens->next->token;
	do_cd(path, tokens, shell);
	return (1);
}
