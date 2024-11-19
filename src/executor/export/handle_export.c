#include "minishell.h"

/// @brief Checks if export cmd is well-written, and if it 
/// meets the required criteria to be executed.
/// @param begin 
/// @param tokens 
/// @param shell 
/// @return 
int	check_export(char *begin, t_tokens *tokens, t_shell *shell)
{
	int	i;

	if (tokens && (!ft_strncmp(tokens->token, "=", 1)
			|| !ft_strncmp(tokens->token, "+=", 2)))
		return (do_error(begin, tokens, shell, ERROR_N_VAL), 1);
	else if (tokens && tokens->type == ARG)
	{
		i = 1;
		if (!ft_isalpha(tokens->token[0])
			&& tokens->token[0] != '_')
			return (do_error(begin, tokens, shell, ERROR_N_VAL), 1);
		while (tokens->token[i]
			&& tokens->token[i] != '=' && tokens->token[i] != '+')
		{
			if (!ft_isalnum(tokens->token[i]))
			{
				do_error(begin, tokens, shell, ERROR_N_VAL);
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

/// @brief Orders alphabetically an array of strings.
/// @param envp 
/// @return 
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

/// @brief Updates the envp vars with the variable to be 
/// exported.
/// @param begin 
/// @param tokens 
/// @param shell 
void	update_env(char *begin, t_tokens *tokens, t_shell *shell)
{
	char	**envp;
	char	**new_envp;
	int		i;

	while (tokens && tokens->type == ARG)
	{
		if (check_export(begin, tokens, shell))
			tokens = tokens->next;
		if (tokens)
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
			add_var(new_envp, tokens);
			free_array(shell->envp, arr_len(shell->envp));
			shell->envp = new_envp;
			tokens = tokens->next;
		}
	}
}

/// @brief Handles the export cmd, followed by the argument 
/// containing the var to be exported.
/// @param tokens 
/// @param shell 
/// @return 
int	ft_export(t_tokens *tokens, t_shell *shell)
{
	char	**envp_print;

	if (ft_strncmp(tokens->token, "export", 7) != 0)
		return (do_error(0, tokens, shell, ERROR_CMD), 1);
	if (tokens->next && tokens->next->type == ARG)
		update_env(tokens->token, tokens->next, shell);
	else
	{
		envp_print = ft_arrdup(shell->envp);
		envp_print = order_alphabetically(envp_print);
		print_export(envp_print);
		free_array(envp_print, arr_len(envp_print));
	}
	return (1);
}
