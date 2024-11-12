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
		if (token[i] == '$' || token[i] == '\"'
			|| token[i] == '\'' || token[i] == ' ')
			break ;
		if (token[i] == '?')
		{
			i++;
			break ;
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
	if (quote_type[0] == '\'' && q->sq == true
		&& q->fe == false)
		q->sq = false;
	else if (quote_type[0] == '\"' && q->dq == true
		&& q->fe == false)
		q->dq = false;
	q->fe = false;
	temp = ft_strdup(&ret[1]);
	free(ret);
	return (temp);
}

void	init_quotes(t_quotes *q)
{
	q->sq = false;
	q->dq = false;
	q->fe = true;
	q->i = 0;
}
