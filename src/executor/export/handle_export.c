#include "minishell.h"

static int	check_export(t_tokens *tokens)
{
	if (tokens->next && tokens->next->next && tokens->next->next->type == ARG)
	{
		// TODO return bad assignment when two args with export
		return (1);
	}
	else if (ft_strncmp(tokens->token, "export", 7) != 0)
	{
		// TODO command not found
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

	if (check_export(token) != 0)
		return (1);
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

void	find_expander(t_tokens	*tokens, t_shell *shell)
{
	t_tokens	*temp;
	char		*new_token;
	char		*token;
	int			i;
	int			is_quoted;

	// If $$ returns pid
	temp = tokens;
	while (temp && temp->token && (*tokens->token != '\''))
	{
		token = temp->token;
		i = 0;
		is_quoted = find_quote(&token[i]);
		while (token[i] && is_quoted != 2)
		{
			if (token[i] == '$')
			{
				i++;
				if (ft_isalpha(token[i]))
				{
					new_token = handle_expander(shell, &token[i]);
					temp->token = new_token;
				}
			}
			i++;
		}
		temp = temp->next;
	}
}

char	*handle_expander(t_shell *shell, char *var)
{
	char	**envp;
	char	*trim;
	char	*new_token;

	envp = shell->envp;
	new_token = NULL;
	var = ft_strtrim(var, "\"");
	while (*envp)
	{
		if (ft_strncmp(*envp, var, ft_strlen(var)) == 0)
		{
			trim = ft_strjoin(var, "=");
			new_token = ft_strtrim(*envp, trim);
			new_token = ft_strtrim(new_token, "\"");
			new_token = ft_strtrim(new_token, "\'");
			break ;
		}
		envp++;
	}
	return (new_token);
}
