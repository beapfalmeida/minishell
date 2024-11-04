#include "minishell.h"

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
	q->i--;
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
		else if (token[q->i] == '$' && q->sq == false)
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
