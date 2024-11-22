/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:44:38 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/22 13:08:52 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_var(t_tokens *tokens, char **env, int j)
{
	char	*to_append;
	char	*appended;

	if (ft_strclen(tokens->token, '\"') > ft_strclen(tokens->token, '+'))
	{
		appended = env[j];
		to_append = tokens->token;
		while (*to_append != '=')
			to_append++;
		to_append++;
		if (has_char(appended, '='))
			appended = ft_strfjoin(appended, to_append, 1);
		else
		{
			appended = ft_strjoin(env[j], "=");
			appended = ft_strfjoin(appended, to_append, 1);
		}
		env[j] = appended;
		return (1);
	}
	return (0);
}

static int	to_replace(t_tokens *tokens, char **env, int j)
{
	if ((has_char(tokens->token, '=')
			&& !strncmp(env[j], tokens->token, ft_strclen(env[j], '='))
			&& !strncmp(env[j], tokens->token, ft_strclen(tokens->token, '=')))
		|| (!has_char(tokens->token, '=')
			&& !strncmp(env[j], tokens->token, ft_strlen(env[j]))
			&& !strncmp(env[j], tokens->token, ft_strclen(tokens->token, '='))))
		return (1);
	return (0);
}

static int	do_nothing(t_tokens *tokens, char **env, int j)
{
	if (has_char(env[j], '=') && !has_char(tokens->token, '=')
		&& !strncmp(env[j], tokens->token, ft_strclen(env[j], '='))
		&& !strncmp(env[j], tokens->token, ft_strclen(tokens->token, '=')))
		return (1);
	return (0);
}

void	add_var(char **env, t_tokens *tokens)
{
	int		i;
	int		j;
	char	*little_string;

	j = 0;
	i = arr_len(env);
	little_string = "+=";
	while (env[j])
	{
		if (to_replace(tokens, env, j))
		{
			free(env[j]);
			env[j] = ft_strdup(tokens->token);
			env[i] = NULL;
			return ;
		}
		else if (do_nothing(tokens, env, j))
			return ;
		else if (ft_strnstr(tokens->token, little_string, ft_strlen(tokens->token)) != NULL
			&& (!strncmp(env[j], tokens->token, ft_strclen(tokens->token, '+'))))
			if (append_var(tokens, env, j))
				return ;
		j++;
	}
	add_envp_var(env, tokens, i);
}

void	print_export(char **envp)
{
	int		i;
	int		equal_sign;
	char	*env;

	while (envp && *envp)
	{
		i = 0;
		equal_sign = 0;
		env = *envp;
		ft_printf_fd(STDOUT_FILENO, "declare -x ");
		while (env[i])
		{
			write(STDOUT_FILENO, &env[i], 1);
			if (env[i] == '=')
			{
				write(STDOUT_FILENO, "\"", 1);
				equal_sign = 1;
			}
			i++;
		}
		if (equal_sign == 1)
			ft_printf_fd(STDOUT_FILENO, "\"");
		ft_printf_fd(STDOUT_FILENO, "\n", 1);
		envp++;
	}
}
