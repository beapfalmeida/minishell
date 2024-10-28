#include "minishell.h"

char	*handle_expander(char **envp, char *var, t_shell *shell)
{
	char	*trim;
	char	*new_token;

	new_token = NULL;
	if (!strncmp(var, "?", 1))
		return (shell->exit_code);
	if (!var || !*var)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp(*envp, var, ft_strclen(var, ' ')) == 0)
		{
			trim = ft_strjoin(var, "=");
			new_token = ft_strdup(*envp);
			new_token += ft_strlen(trim);
			new_token = ft_strtrim(new_token, "\"");
			new_token = ft_strtrim(new_token, "\'");
			break ;
		}
		envp++;
	}
	return (new_token);
}  

char	*get_var(char *token)
{
	int		i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' || token[i] == '\"' || token[i] == '\'')
			break ;
		i++;
	}
	token[i] = '\0';
	return (token);
}

char	*skip_quote(char *token, const char *quote_type, bool *sq, bool *dq, bool *first_encounter)
{
	char	*ret;
	char	*temp;

	ret = ft_strdup(token);
	if (quote_type[0] == '\'' && *sq == true && *first_encounter == false)
		*sq = false;
	else if (quote_type[0] == '\"' && *dq == true && *first_encounter == false)
		*dq = false;
	*first_encounter = false;
	temp = ft_strdup(&ret[1]);
	free(ret);
	return (temp);
}

//TODO: free string_joins && norminette
t_tokens	*handle_quotes(t_tokens *tokens, t_shell *shell)
{
	t_tokens	*ret;
	char	*token;
	char	*temp;
	char	*envp_var;
	bool	dq;
	bool	sq;
	bool	first_encounter;
	int		i;

	ret = tokens;

	sq = false;
	dq = false;
	first_encounter = true;
	while (tokens && tokens->token)
	{
		sq = false;
		dq = false;
		first_encounter = true;
		token = tokens->token;
		i = 0;
		while (token[i])
		{
			first_encounter = true;
			if (token[i] == '\'' && dq == false)
			{
				sq = !sq;
				char *trimed = skip_quote(&token[i], "\'", &sq, &dq, &first_encounter);
				token[i] = '\0';
				token = ft_strfjoin(token, trimed, 3);
				continue ;
			}
			else if (token[i] == '\"' && sq == false)
			{
				dq = !dq;
				char *trimed = skip_quote(&token[i], "\"", &sq, &dq, &first_encounter);
				token[i] = '\0';
				token = ft_strfjoin(token, trimed, 3);
				continue ;
			}
			if (token[i] == '$' && sq == false)
			{
				if (token[i + 1] && token[i + 1] != ' ' && token[i + 1] != '$' 
					&& token[i+1] != '\"' && token[i+1] != '\'' && check_new_token(&token[i+1]) == 3)
				{
					envp_var = get_var(ft_strdup(&token[i + 1]));
					temp = ft_strdup(&token[i + ft_strlen(envp_var) + 1]);
					token[i] = '\0';
					token = ft_strjoin(token, handle_expander(shell->envp, envp_var, shell));
					i += ft_strlen(handle_expander(shell->envp, envp_var, shell));
					token = ft_strfjoin(token, temp, 3);
					free(envp_var);
				}
				else
					i++; 
				if (!*token)
				{
					tokens->token = token;
					tokens->type = SKIP;
					break ;
				}
				continue ;
			}
			else
				i++;
		}
		tokens->token = token;
		tokens = tokens->next;
	}
	return (ret);
}
