#include "minishell.h"

int	check_export(t_tokens *tokens, t_shell *shell)
{
	int	i;

	if (ft_strncmp(tokens->token, "export", 7) != 0)
		return (do_error(tokens, shell, ERROR_CMD), 1);
	if (tokens->next && (!ft_strncmp(tokens->next->token, "=", 1)
			|| !ft_strncmp(tokens->next->token, "+=", 2)))
		return (do_error(tokens, shell, ERROR_N_VAL), 1);
	else if (tokens->next && tokens->next->type == ARG)
	{
		i = 1;
		if (!ft_isalpha(tokens->next->token[0])
			&& tokens->next->token[0] != '_')
			return (do_error(tokens, shell, ERROR_N_VAL), 1);
		while (tokens->next->token[i]
			&& tokens->next->token[i] != '=' && tokens->next->token[i] != '+')
		{
			if (!ft_isalnum(tokens->next->token[i]))
			{
				do_error(tokens, shell, ERROR_N_VAL);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

static void	swap(int low, int i, char **envp)
{
	char	*temp;

	temp = envp[i];
	envp[i] = envp[low];
	envp[low] = temp;
}

char	**order_alphabetically(char **envp)
{
	int		i;
	int		j;
	int		low;

	i = 0;
	while (envp[i])
	{
		low = i;
		j = i + 1;
		while (envp[j])
		{
			if (ft_strncmp(envp[low], envp[j], ft_strlen(envp[j])) > 0)
				low = j;
			else if (ft_strncmp(envp[low], envp[j], ft_strlen(envp[low])) > 0)
				low = j;
			j++;
		}
		if (low != i)
			swap(low, i, envp);
		i++;
	}
	return (envp);
}

void	update_env(t_tokens *tokens, t_shell *shell)
{
	char	**envp;
	char	**new_envp;
	int		i;

	while (tokens->next && tokens->next->type == ARG)
	{
		envp = shell->envp;
		new_envp = malloc(sizeof(char *) * (arr_len(envp) + 2));
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

int	ft_export(t_tokens *tokens, t_shell *shell)
{
	char	**envp_print;

	if (check_export(tokens, shell) != 0)
		return (1);
	if (tokens->next && tokens->next->type == ARG)
		update_env(tokens, shell);
	else
	{
		envp_print = ft_arrdup(shell->envp);
		envp_print = order_alphabetically(envp_print);
		print_export(envp_print);
		free_array(envp_print, arr_len(envp_print));
	}
	return (1);
}
