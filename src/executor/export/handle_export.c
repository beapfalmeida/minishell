#include "minishell.h"

char	order_alphabetically(char **envp)
{
	int		i;
	int		j;
	int		lowest_index;
	int		lowest_diff;
	char	**ret;

	i = 0;
	while (envp[i])
	{
		lowest_index = i;
		lowest_diff = ft_strncmp(envp[i], envp[j], ft_strlen(envp[j]));
		ret = malloc(sizeof(ret) + 1);
		while (envp[j])
		{
			j = 0;
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[j])) > lowest_diff)
			{
				lowest_diff = ft_strncmp(envp[i], envp[j], ft_strlen(envp[j]));
				lowest_index = j;
				j++;
			}
		}
		ft_strjoin(ret[i], envp[lowest_index]);
		i++;
	}
	return (0);
}

int	ft_export(t_tokens *token, t_shell *shell)
{
	char	**envp;
	char	**new_envp;

	envp = shell->envp;
	if (token->next->token && token->next->type == ARG)
	{
		new_envp = malloc(sizeof(envp) + 1);
		while (*envp)
		{
			*new_envp = ft_strdup(*envp);
			envp++;
			new_envp++;
		}
		order_alphabetically(envp);
		ft_strjoin(*new_envp, token->token);
		envp = new_envp;
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
