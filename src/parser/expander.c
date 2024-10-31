#include "minishell.h"

char	*handle_expander(char **envp, char *var, t_shell *shell)
{
	char	*trim;
	char	*new_token;

	new_token = NULL;
	if (!strncmp(var, "?", 1))
		return (ft_itoa(shell->exit_code));
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
		if (token[i] == '$' || token[i] == '\"' || token[i] == '\'' || token[i] == ' ')
			break ;
		if (token[i] == '?')
		{
			i++;
			break;
		}
		i++;
	}
	token[i] = '\0';
	return (token);
}

char	*skip_quote(char *token, const char *quote_type, t_quotes *q)
{
	char	*ret;
	char	*temp;

	ret = ft_strdup(token);
	if (quote_type[0] == '\'' && q->sq == true && q->first_encounter == false)
		q->sq = false;
	else if (quote_type[0] == '\"' && q->dq == true && q->first_encounter == false)
		q->dq = false;
	q->first_encounter = false;
	temp = ft_strdup(&ret[1]);
	free(ret);
	return (temp);
}

void	init_quotes(t_quotes *q)
{
	q->sq = false;
	q->dq = false;
	q->first_encounter = true;
	q->i = 0;
}

char	*found_quote(char *token, t_quotes *q, int type)
{
	char *trimed;

	if (type == '\'')
		q->sq = !q->sq;
	else if (type == '\"')
		q->dq = !q->dq;
	trimed = skip_quote(&token[q->i], "\"", q);
	token[q->i] = '\0';
	token = ft_strfjoin(token, trimed, 3);
	return (token);
}

char	*expand(char *token, t_shell *shell, t_quotes *q)
{
	char	*temp;
	char	*envp_var;

	envp_var = get_var(ft_strdup(&token[q->i + 1]));
	temp = ft_strdup(&token[q->i + ft_strlen(envp_var) + 1]);
	token[q->i] = '\0';
	token = ft_strjoin(token, handle_expander(shell->envp, envp_var, shell));
	q->i += ft_strlen(handle_expander(shell->envp, envp_var, shell));
	token = ft_strfjoin(token, temp, 3);
	free(envp_var);
	return (token);
}

char	*process_token(char *token, t_tokens *tokens, t_shell *shell, t_quotes *q)
{
	while (token[q->i])
	{
		q->first_encounter = true;
		if (token[q->i] == '\'' && q->dq == false)
			token = found_quote(token, q, '\'');
		else if (token[q->i] == '\"' && q->sq == false)
			token = found_quote(token, q, '\"');
		if (token[q->i] == '$' && q->sq == false)
		{
			if (token[q->i + 1] && token[q->i + 1] != ' ' && token[q->i + 1] != '$'
				&& token[q->i + 1] != '\"' && token[q->i + 1] != '\''
				&& check_new_token(&token[q->i + 1]) == 3)
				token = expand(token, shell, q);
			else
				q->i++; 
			if (!*token)
			{
				tokens->type = SKIP;
				break ;
			}
		}
		else
			q->i++;
	}
	return (token);
}

t_tokens	*handle_quotes(t_tokens *tokens, t_shell *shell)
{
	t_tokens	*ret;
	char	*token;
	t_quotes	q;

	ret = tokens;
	init_quotes(&q);
	while (tokens && tokens->token)
	{
		init_quotes(&q);
		token = tokens->token;
		token = process_token(token, tokens, shell, &q);
		if (!*token)
			tokens->type = SKIP;
		tokens->token = token;
		tokens = tokens->next;
	}
	return (ret);
}
