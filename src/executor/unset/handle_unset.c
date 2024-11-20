#include "minishell.h"

/// @brief Checks if unset is well-written.
/// @param tokens 
/// @param shell 
/// @return 0 if ok, 1 if mistake.
static int	check_unset(t_tokens *tokens, t_shell *shell)
{
	if (ft_strncmp(tokens->token, "unset", 6) != 0)
	{
		do_error(0, tokens, shell, ERROR_CMD);
		return (1);
	}
	return (0);
}

static void	do_unset(t_tokens *temp, t_shell *shell)
{
	char		**envp;
	char		**new_envp;
	char		**tmp;

	while (temp)
	{
		envp = shell->envp;
		new_envp = malloc(sizeof(char *) * (arr_len(envp) + 1));
		tmp = new_envp;
		while (*envp)
		{
			if (ft_strncmp(*envp, temp->token, ft_strclen(*envp, '=')) != 0)
			{
				*new_envp = *envp;
				new_envp++;
			}
			else
				free(*envp);
			envp++;
		}
		*new_envp = NULL;
		free(shell->envp);
		shell->envp = tmp;
		temp = temp->next;
	}
}

/// @brief Undos exported variable.
/// @param tokens 
/// @param shell 
/// @return 
int	ft_unset(t_tokens *tokens, t_shell *shell)
{
	t_tokens	*temp;

	if (check_unset(tokens, shell) != 0)
		return (1);
	if (!tokens->next)
		return (1);
	temp = tokens->next;
	do_unset(temp, shell);
	return (1);
}
