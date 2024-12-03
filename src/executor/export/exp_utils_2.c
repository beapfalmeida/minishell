/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:42:13 by jsobreir          #+#    #+#             */
/*   Updated: 2024/12/03 11:01:47 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_envp_var(char **env, t_tokens *tokens, int i)
{
	char	*append_one;
	char	*two;
	char	*token;
	char	*little_string;

	token = tokens->token;
	little_string = "+=";
	if (ft_strnstr(tokens->token, little_string, ft_strlen(tokens->token)))
	{
		append_one = ft_substr(token, 0, ft_strclen(token, '+'));
		two = ft_substr(token, ft_strclen(token, '+') + 1, ft_strlen(token));
		env[i] = ft_strfjoin(append_one, two, 3);
	}
	else
		env[i] = ft_strdup(token);
	env[i + 1] = NULL;
}

void	copy_envp(char **envp, char **new_envp, int i)
{
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
}
