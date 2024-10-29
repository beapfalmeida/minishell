#include "minishell.h"

static int	check_export(t_tokens *tokens, t_shell *shell)
{
	if (ft_strncmp(tokens->token, "export", 7) != 0)
	{
		do_error(tokens, shell, ERROR_CMD);
		return (1);
	}
	if (tokens->next && 
		(!ft_strncmp(tokens->next->token, "=", 1) || !ft_strncmp(tokens->next->token, "+=", 2)))
	{
		do_error(tokens, shell, ERROR_N_VAL);
	}
	return (0);
}

char	**order_alphabetically(char **envp)
{
	int		i;
	int		j;
	int		lowest_index;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		lowest_index = i;
		j = i + 1;
		while (envp[j])
		{
			if (ft_strncmp(envp[lowest_index], envp[j], ft_strlen(envp[j])) > 0)
				lowest_index = j;
			else if (ft_strncmp(envp[lowest_index], envp[j], ft_strlen(envp[lowest_index])) > 0)
				lowest_index = j;
			j++;
		}
		if (lowest_index != i)
		{
			temp = envp[i];
			envp[i] = envp[lowest_index];
			envp[lowest_index] = temp;
		}
		i++;
	}
	return (envp);
}

static void	add_var(char **env, t_tokens *tokens)
{
	int 	i;
	int 	j;
	char	*temp;
	char	*appended;

	j = 0;
	i = arr_len(env);
	while (env[j])
	{
		if (has_char(tokens->token, '=') &&
			!strncmp(env[j], tokens->token, ft_strclen(env[j], '=')) &&
			!strncmp(env[j], tokens->token, ft_strclen(tokens->token, '=')))
		{
			if (has_char(tokens->token, '='))
				env[j] = ft_strdup(tokens->token);
			env[i] = NULL;
			return ;
		}
		else if (!has_char(tokens->token, '=') &&
			!strncmp(env[j], tokens->token, ft_strlen(env[j])) &&
			!strncmp(env[j], tokens->token, ft_strlen(tokens->token)))
		{
			env[j] = ft_strdup(tokens->token);
			env[i] = NULL;
			return ;
		}
		else if (has_char(tokens->token, '+') && !strncmp(env[j], tokens->token, ft_strclen(tokens->token, '+')))
		{
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
				return ;
			}
		}
		j++;
	}
	env[i] = ft_strdup(tokens->token);
	env[i + 1] = NULL;
}

static void	print_export(char **envp)
{
	int i;
	int	equal_sign;
	char	*env;

	while (envp && *envp)
	{
		i = 0;
		equal_sign = 0;
		env = *envp;
		ft_printf_fd(STDOUT_FILENO, "declare -x ");
		while (env[i])
		{
			ft_printf_fd(STDOUT_FILENO, &env[i], 1);
			if (env[i] == '=')
			{
				ft_printf_fd(STDOUT_FILENO, "\"", 1);
				equal_sign = 1;
			}
			i++;
		}
		if (equal_sign == 1)
			ft_printf_fd(STDOUT_FILENO, "\"", 1);
		ft_printf_fd(STDOUT_FILENO, "\n", 1);
		envp++;
	}
}

int	ft_export(t_tokens *tokens, t_shell *shell)
{
	int		i;
	char	**envp;
	// char	**temp_envp;
	char	**new_envp;
	char	**envp_print;

	if (check_export(tokens, shell) != 0)
		return (1);
	envp = shell->envp;
	envp_print = ft_arrdup(envp);
	if (tokens->next && tokens->next->type == ARG)
	{
		while (tokens->next && tokens->next->type == ARG)
		{
			envp = shell->envp;
			new_envp = malloc(sizeof(char *) * (arr_len(envp) + 2));
			// temp_envp = envp;
			i = 0;
			while (envp[i])
			{
				new_envp[i] = ft_strdup(envp[i]);
				i++;
			}
			new_envp[i] = NULL;
			add_var(new_envp, tokens->next);
			free_array(shell->envp, arr_len(shell->envp));
			shell->envp = new_envp;
			tokens = tokens->next;
		}
	}
	else
	{
		envp_print = order_alphabetically(envp_print);
		print_export(envp_print);
		free_array(envp_print, arr_len(envp_print));
	}
	return (1);
}
