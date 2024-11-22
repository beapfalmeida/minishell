/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:44:56 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/20 15:44:57 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isbuiltin(t_tokens *token)
{
	if (ft_strncmp(token->token, "pwd", 3) == 0)
		return (PWD);
	else if (ft_strncmp(token->token, "cd", 2) == 0)
		return (CD);
	else if (ft_strncmp(token->token, "echo", 4) == 0)
		return (ECHO);
	else if (ft_strncmp(token->token, "env", 3) == 0)
		return (ENV);
	else if (ft_strncmp(token->token, "export", 6) == 0)
		return (EXPORT);
	else if (ft_strncmp(token->token, "unset", 6) == 0)
		return (UNSET);
	else
		return (0);
}

int	ft_exec_builtin(t_tokens *token, t_shell *shell, int type_builtin)
{
	if (shell->fds->in < 0 && shell->n_pipes != 1)
		return (1);
	if (type_builtin == 0)
		return (0);
	if (type_builtin == PWD)
		return (ft_pwd(token, shell));
	else if (type_builtin == CD)
		return (ft_cd(token, shell));
	else if (type_builtin == ECHO)
		return (ft_echo(token, shell));
	else if (type_builtin == ENV)
		return (ft_env(shell, token));
	else if (type_builtin == EXPORT)
		return (ft_export(token, shell));
	else if (type_builtin == UNSET)
		return (ft_unset(token, shell));
	return (1);
}
