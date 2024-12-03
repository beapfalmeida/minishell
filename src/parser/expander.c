/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:45:17 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/23 15:56:33 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief If quote is found, this function skips that quote,
/// if not inside unclosed brackets.
/// @param token Pointer to the tokens struct.
/// @param q Pointer to the quotes struct.
/// @param type Type of quote in ASCII.
/// @return 
char	*found_quote(t_tokens *tokens, char *token, t_quotes *q, int type)
{
	char	*trimed;
	char	qtype[1];

	if (type == '\'')
		q->sq = !q->sq;
	else if (type == '\"')
		q->dq = !q->dq;
	*qtype = (char)type;
	trimed = skip_quote(&token[q->i], qtype, q);
	token[q->i] = '\0';
	token = ft_strfjoin(token, trimed, 3);
	while (*token == type)
	{
		trimed = skip_quote(&token[q->i], qtype, q);
		token[q->i] = '\0';
		token = ft_strfjoin(token, trimed, 3);
	}
	if (q->i)
		q->i--;
	tokens->expanded = true;
	return (token);
}

/// @brief Expand an env variable.
/// @param token Pointer to the tokens struct.
/// @param shell Pointer to the shell variables struct.
/// @param q Pointer to the quotes struct.
/// @return String containing expanded token.
char	*expand(char *token, t_shell *shell, t_quotes *q)
{
	char	*temp;
	char	*envp_var;
	char	*expanded;

	envp_var = get_var(ft_strdup(&token[q->i + 1]));
	temp = ft_strdup(&token[q->i + ft_strlen(envp_var) + 1]);
	token[q->i] = '\0';
	expanded = handle_expander(shell->envp, envp_var, shell);
	token = ft_strfjoin(token, expanded, 1);
	q->i += ft_strlen(expanded);
	free(expanded);
	token = ft_strfjoin(token, temp, 3);
	free(envp_var);
	return (token);
}

/// @brief Looks for quotes and expanders inside a token and 
/// treats them accordingly.
/// @param token String containing the current token being 
/// treated.
/// @param tokens Pointer to the tokens struct.
/// @param shell Pointer to the shell variables struct.
/// @param q Pointer to the quotes struct.
/// @return String containing treated token.
char	*process_token(char *token, t_tokens *tokens,
	t_shell *shell, t_quotes *q)
{
	while (token && token[q->i])
	{
		q->fe = true;
		if (token[q->i] == '\'' && q->dq == false)
			token = found_quote(tokens, token, q, '\'');
		else if (token[q->i] == '\"' && q->sq == false)
			token = found_quote(tokens, token, q, '\"');
		if (token[q->i] == '$' && q->sq == false)
		{
			if (token[q->i + 1] && token[q->i + 1] != ' '
				&& token[q->i + 1] != '$' && token[q->i + 1] != '\"'
				&& token[q->i + 1] != '\'' && check_nt(&token[q->i + 1]) == 3)
				token = expand(token, shell, q);
			else
				q->i++;
			if (!*token)
			{
				tokens->type = NOT_SKIP;
				break ;
			}
		}
		else if (token[q->i])
			q->i++;
	}
	return (token);
}

/// @brief Looks for quotes and expanders in every token. 
/// Expands if not inside single-quotes.
/// @param tokens Pointer to the tokens struct.
/// @param shell Pointer to the shell variables struct.
/// @return Pointer to the new, treated, tokens list.
t_tokens	*handle_quotes(t_tokens *tokens, t_shell *shell)
{
	t_tokens	*ret;
	char		*token;
	t_quotes	q;

	ret = tokens;
	init_quotes(&q);
	while (tokens && tokens->token)
	{
		init_quotes(&q);
		token = tokens->token;
		token = process_token(token, tokens, shell, &q);
		if (!*token && tokens->expanded && tokens->type != NOT_SKIP)
			tokens->type = SKIP;
		tokens->token = token;
		tokens = tokens->next;
	}
	tokens = ret;
	while (tokens)
	{
		if (*(tokens->token) != '\0')
			return (ret);
		tokens = tokens->next;
	}
	return (ret);
}
