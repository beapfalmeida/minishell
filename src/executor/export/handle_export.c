#include "minishell.h"

static int	check_export(t_tokens *tokens, t_shell *shell)
{
	if (ft_strncmp(tokens->token, "export", 7) != 0)
	{
		do_error(tokens, shell, ERROR_CMD);
		return (1);
	}
	return (0);
}

void	order_alphabetically(char **envp)
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
}

static void	add_var(char **temp_envp, char **env, t_tokens *tokens)
{
	int	i;
	int j;

	j = 0;
	i = 0;
	while (temp_envp[i])
	{
		env[i] = ft_strdup(temp_envp[i]);
		i++;
	}
	while (env[j])
	{
		if (!strncmp(env[j], tokens->token, ft_strclen(tokens->token, '=')))
		{
			if (has_char(tokens->token, '='))
				env[j] = ft_strdup(tokens->token);
			env[i] = NULL;
			return ;
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
		write(1, "declare -x ", 11);
		while (env[i])
		{
			write(1, &env[i], 1);
			if (env[i] == '=')
			{
				write(1, "\"", 1);
				equal_sign = 1;
			}
			i++;
		}
		if (equal_sign == 1)
			write(1, "\"", 1);
		write(1, "\n", 1);
		envp++;
	}
}

int	ft_export(t_tokens *tokens, t_shell *shell)
{
	char	**envp;
	char	**temp_envp;
	char	**new_envp;

	if (check_export(tokens, shell) != 0)
		return (1);
	envp = shell->envp;
	if (tokens->next && tokens->next->type == ARG)
	{
		while (tokens->next && tokens->next->type == ARG)
		{
			envp = shell->envp;
			new_envp = malloc(sizeof(char *) * (arr_len(envp) + 2));
			temp_envp = envp;
			add_var(temp_envp, new_envp, tokens->next);
			order_alphabetically(new_envp);
			free_array(shell->envp, arr_len(shell->envp));
			shell->envp = new_envp;
			tokens = tokens->next;
		}
	}
	else
		print_export(envp);
	return (1);
}
