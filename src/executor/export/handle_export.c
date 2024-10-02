#include "minishell.h"

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
			{
				lowest_index = j;
			}
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

int	ft_export(t_tokens *token, t_shell *shell)
{
	char	**envp;
	char	**temp_envp;
	char	**new_envp;
	int		i;

	envp = shell->envp;
	if (token->next && token->next->type == ARG)
	{
		while (token->next && token->next->type == ARG)
		{
			envp = shell->envp;
			new_envp = malloc(sizeof(char *) * (arr_len(envp) + 2));
			temp_envp = envp;
			i = 0;
			while (temp_envp[i])
			{
				new_envp[i] = ft_strdup(temp_envp[i]);
				i++;
			}
			new_envp[i] = ft_strdup(token->next->token);
			new_envp[i + 1] = NULL;
			order_alphabetically(new_envp);
			shell->envp = new_envp;
			token = token->next;
		}
	}
	else
	{
		while (*envp)
		{
			printf("declare -x ");
			printf("%s\n", *envp);
			envp++;
		}
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

