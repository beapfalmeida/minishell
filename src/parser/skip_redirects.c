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

t_tokens	*skip_redirects(t_tokens *tokens)
{
	t_tokens	*new_tokens;

	new_tokens = NULL;
	while (tokens && tokens->token)
	{
		if (is_redirect(tokens))
		{
			tokens = tokens->next;
			while (tokens && (tokens->type == INPUT
					|| tokens->type == OUTPUT || tokens->type == LIMITER))
				tokens = tokens->next;
		}
		if (dont_skip(tokens))
		{
			add_back_list(&new_tokens, new_node(tokens->token, 0));
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
