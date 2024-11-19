#include "minishell.h"

/// @brief Handles tokens that require expansion by getting the corresponding environment variable.
/// @param envp Pointer to the Environment Variables array.
/// @param var Variable to be expanded (searched for in envp).
/// @param shell Pointer to the shell struct.
/// @return 
char	*handle_expander(char **envp, char *var, t_shell *shell)
{
	char	*trim;
	char	*new_token;
	char	*result;

	new_token = NULL;
	trim = NULL;
	if (!strncmp(var, "?", 1))
		return (ft_itoa(shell->exit_code));
	if (!var || !*var)
		return (NULL);
	trim = ft_strjoin(var, "=");
	while (*envp)
	{
		if (ft_strncmp(*envp, trim, ft_strlen(trim)) == 0)
		{
			new_token = ft_strdup(*envp + ft_strlen(trim));
			result = ft_strtrim(new_token, "\"");
			free(new_token);
			new_token = result;
			result = ft_strtrim(new_token, "\'");
			free(new_token);
			new_token = result;
			break ;
		}
		envp++;
	}
	free(trim);
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

char	*skip_quote(char *token, char *quote_type, t_quotes *q)
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
