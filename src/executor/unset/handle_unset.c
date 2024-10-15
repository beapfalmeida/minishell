#include "minishell.h"

int	check_unset(t_tokens *tokens, t_shell *shell)
{
	if (ft_strncmp(tokens->token, "unset", 6) != 0)
	{
		do_error(tokens, shell, ERROR_CMD);
		return (1);
	}
	// if (tokens->next->next && tokens->next->next->type == ARG)
	// {
	// 	// TODO return bad assignment
	// 	return (1);
	// } nao entendi para que isto servia e estava a provocar core dumped quando so tinha "unset" como unico token;
	return (0);
}
int	ft_unset(t_tokens *tokens, t_shell *shell)
{
	char	**envp;
	char	**new_envp;
	char	**tmp;
	int		found;
	t_tokens	*temp;

	if (check_unset(tokens, shell) != 0)
		return (1);
	if (!tokens->next)
		return (1);
	found = 0;
	temp = tokens->next;
	while (temp)
	{
		envp = shell->envp;
		new_envp = malloc(sizeof(char *) * (arr_len(envp) + 1));
		tmp = new_envp;
		while (*envp)
		{
			if (ft_strncmp(*envp, temp->token, ft_strlen(temp->token)) != 0)
			{
				*new_envp = *envp;
				new_envp++;
				found = 1;
			}
			envp++;
		}
		*new_envp = NULL;
		shell->envp = tmp;
		free(*new_envp);
		temp = temp->next;
	}
	return (1);
}
