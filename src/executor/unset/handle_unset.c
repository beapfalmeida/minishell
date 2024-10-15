#include "minishell.h"

int	check_unset(t_tokens *tokens, t_shell *shell)
{
	if (tokens->next->next && tokens->next->next->type == ARG)
	{
		// TODO return bad assignment ?????? no comprendo
		return (1);
	}
	else if (ft_strncmp(tokens->token, "unset", 6) != 0)
	{
		do_error(tokens, shell, ERROR_CMD);
		return (1);
	}
	return (0);
}
int	ft_unset(t_tokens *tokens, t_shell *shell)
{
	char	**envp;
	char	*token;
	char	**new_envp;
	char	**tmp;
	int		found;

	if (check_unset(tokens, shell) != 0)
		return (1);
	token = tokens->next->token;
	envp = shell->envp;
	found = 0;
	if (tokens->next)
	{
		new_envp = malloc(sizeof(char *) * (arr_len(envp) + 1));
		tmp = new_envp;
		while (*envp)
		{
			if (ft_strncmp(*envp, token, ft_strlen(token)) != 0)
			{
				*new_envp = *envp;
				new_envp++;
				found = 1;
			}
				envp++;
		}
		*new_envp = NULL;
		if (found == 0)
			free(*new_envp);
		shell->envp = tmp;
	}
	return (0);
}
