/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:42:13 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/22 13:07:44 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_envp_var(char **env, t_tokens *tokens, int	i)
{
	char	*append_one;
	char	*append_two;
	char	*token;
	char	*little_string;

	token = tokens->token;
	little_string = "+=";
	if (ft_strnstr(tokens->token, little_string, ft_strlen(tokens->token)) != NULL)
	{
		append_one = ft_substr(token, 0, ft_strclen(token, '+'));
		append_two = ft_substr(token, ft_strclen(token, '+') + 1, ft_strlen(token));
		env[i] = ft_strfjoin(append_one, append_two, 3);
	}
	else
		env[i] = ft_strdup(token);
	env[i + 1] = NULL;
}
