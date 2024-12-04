/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:45:20 by jsobreir          #+#    #+#             */
/*   Updated: 2024/12/04 12:16:36 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Handles tokens that require expansion by getting the 
/// corresponding environment variable.
/// @param envp Pointer to the Environment Variables array.
/// @param var Variable to be expanded (searched for in envp).
/// @param shell Pointer to the shell struct.
/// @return String containing expanded token.
char	*handle_expander(char **envp, char *var, t_shell *shell)
{
	char	*trim;
	char	*new_token;
	char	*result;

	new_token = NULL;
	trim = NULL;
	if (!ft_strncmp(var, "?", 1))
		return (ft_itoa(shell->exit_code));
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
	return (free(trim), new_token);
}

/// @brief Null terminates the variable name to look for in 
/// the environment variables.
/// @param token Variable name to null-terminate.
/// @return Null-terminated variable name.
char	*get_var(char *token)
{
	int		i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '?')
		{
			i++;
			break ;
		}
		else if (token[i] == '$' || token[i] == '\"'
			|| token[i] == '\'' || !ft_isalnum(token[i]))
			break ;
		i++;
	}
	token[i] = '\0';
	return (token);
}

/// @brief Function to skip a given quote, if no unclosed 
/// brackets detected.
/// @param token String containing the token to remove quotes from.
/// @param quote_type String containing quotes of a given type.
/// @param q Pointer to struct.
/// @return 
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

/// @brief Innitializes the quotes struct variables.
/// @param q Pointer to the quotes struct.
void	init_quotes(t_quotes *q)
{
	q->sq = false;
	q->dq = false;
	q->fe = true;
	q->i = 0;
}
