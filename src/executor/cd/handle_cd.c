/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:44:22 by jsobreir          #+#    #+#             */
/*   Updated: 2024/12/03 17:24:19 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_path(char *path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if ((path[i] >= '0' && path[i] <= '9')
			|| ((path[i] > 64 && path[i] < 91)
				|| (path[i] > 96 && path[i] < 123))
			|| path[i] == '/' || path[i] == '_'
			|| path[i] == '.' || path[i] == '~'
			|| path[i] == '-')
			i++;
		else
			return (0);
	}
	return (1);
}

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

	if (*path == '\0')
		return (free(path), 1);
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
	if (!tokens->next || !ft_strncmp(tokens->next->token, "~/", 2)
		|| !ft_strncmp(tokens->next->token, "~", 2))
	{
		path = ft_strdup(getenv("HOME"));
		if (tokens->next && !ft_strncmp(tokens->next->token, "~/", 2))
			path = ft_strfjoin(path, &tokens->next->token[1], 1);
	}
	else if (!ft_strncmp(tokens->next->token, "-", 2))
	{
		flag = 1;
		path = ft_strdup(shell->last_path);
	}
	else if (is_path(tokens->next->token))
		path = ft_strdup(tokens->next->token);
	else
		return (do_error(0, tokens->next, shell, ERROR_INVO), 1);
	do_cd(path, tokens, shell);
	return (1);
}
