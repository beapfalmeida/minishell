/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:45:42 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/20 15:45:43 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dont_skip(t_tokens *tokens)
{
	if (tokens && tokens->token && !(tokens->type == REDIRECT_IN
			|| tokens->type == REDIRECT_OUT || tokens->type == APPEND_IN
			|| tokens->type == APPEND_OUT || tokens->type == NOT_SKIP))
		return (1);
	return (0);
}

static int	is_redirect(t_tokens *tokens)
{
	if (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT
		|| tokens->type == APPEND_IN || tokens->type == APPEND_OUT
		|| tokens->type == NOT_SKIP)
		return (1);
	return (0);
}

static void	skipping(t_tokens **tokens)
{
	free((*tokens)->token);
	*tokens = (*tokens)->next;
	while ((*tokens) && ((*tokens)->type == INPUT
			|| (*tokens)->type == OUTPUT || (*tokens)->type == LIMITER))
	{
		free((*tokens)->token);
		*tokens = (*tokens)->next;
	}
}

t_tokens	*skip_redirects(t_tokens *tokens)
{
	t_tokens	*new_tokens;
	t_tokens	*node;

	new_tokens = NULL;
	while (tokens && tokens->token)
	{
		if (is_redirect(tokens))
			skipping(&tokens);
		if (dont_skip(tokens))
		{
			node = new_node(tokens->token, 0);
			node->expanded = tokens->expanded;
			add_back_list(&new_tokens, node);
			tokens = tokens->next;
		}
	}
	if (new_tokens)
	{
		assign_types(&new_tokens);
		return (new_tokens);
	}
	return (0);
}
