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
		// Swap the strings
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

	envp = shell->envp;
	if (token->next && token->next->type == ARG)
	{
		new_envp = malloc(sizeof(envp) + 1);
		temp_envp = envp;
		while (*temp_envp)
		{
			*new_envp = ft_strdup(*temp_envp);
			temp_envp++;
			new_envp++;
		}
		order_alphabetically(envp);
		shell->envp = envp;
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
