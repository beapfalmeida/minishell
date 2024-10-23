#include "minishell.h"

void	skip_type_redirect(t_tokens *tokens, t_tokens **new_tokens)
{
	while (tokens && tokens->token)
	{
		if (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT 
				|| tokens->type == APPEND_IN || tokens->type == APPEND_OUT
				|| tokens->type == SKIP)
		{
			tokens = tokens->next;
			while (tokens && (tokens->type == INPUT 
				|| tokens->type == OUTPUT || tokens->type == LIMITER))
				tokens = tokens->next;
		}
		if (tokens && tokens->token && !(tokens->type == REDIRECT_IN 
				|| tokens->type == REDIRECT_OUT || tokens->type == APPEND_IN 
				|| tokens->type == APPEND_OUT || tokens->type == SKIP))
		{
			if (tokens->prev && tokens->prev->type == SKIP)
				add_back_list(new_tokens, new_node(tokens->token, NOT_FILE));
			else
				add_back_list(new_tokens, new_node(tokens->token, 0));
			tokens = tokens->next;
		}
	}
}

t_tokens	*skip_redirects(t_tokens *original)
{
	t_tokens	*new_tokens;
	t_tokens	*tokens;

	new_tokens = NULL;
	tokens = original;
	skip_type_redirect(tokens, &new_tokens);
	if (new_tokens)
	{
		assign_types(&new_tokens);
		lstclear(&original);
		return (new_tokens);
	}
	else
		return (0);
}
