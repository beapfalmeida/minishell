#include "minishell.h"

static int	append_var(t_tokens *tokens, char **env, int j)
{
	char	*temp;
	char	*appended;

	if (ft_strclen(tokens->token, '\"') > ft_strclen(tokens->token, '+'))
	{
		temp = tokens->token;
		while (*temp != '=')
			temp++;
		temp++;
		ft_strtrim(temp, "\"");
		if (has_char(env[j], '='))
		{
			ft_strtrim(env[j], "\"");
			appended = ft_strjoin(env[j], temp);
		}
		else
		{
			appended = ft_strjoin(env[j], "=");
			appended = ft_strfjoin(appended, temp, 1);
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
	int	i;
	int	j;

	j = 0;
	i = arr_len(env);
	while (env[j])
	{
		if (to_replace(tokens, env, j))
		{
			env[j] = ft_strdup(tokens->token);
			env[i] = NULL;
			return ;
		}
		else if (do_nothing(tokens, env, j))
			return ;
		else if (has_char(tokens->token, '+')
			&& !strncmp(env[j], tokens->token, ft_strclen(tokens->token, '+')))
		{
			if (append_var(tokens, env, j))
				return ;
		}
		j++;
	}
	env[i] = ft_strdup(tokens->token);
	env[i + 1] = NULL;
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
