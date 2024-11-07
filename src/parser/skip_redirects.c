#include "minishell.h"

t_tokens	*skip_redirects(t_tokens *tokens)
{
	t_tokens	*new_tokens;

	new_tokens = NULL;
	while (tokens && tokens->token)
	{
		if (tokens->type == REDIRECT_IN || tokens->type == REDIRECT_OUT 
			|| tokens->type == APPEND_IN || tokens->type == APPEND_OUT 
			|| tokens->type == NOT_SKIP)
		{
			//free(tokens->token);
			tokens = tokens->next;
			while (tokens && (tokens->type == INPUT 
				|| tokens->type == OUTPUT || tokens->type == LIMITER))
				{
					//free(tokens->token);
					tokens = tokens->next;
				}
		}
		if (tokens && tokens->token && !(tokens->type == REDIRECT_IN 
			|| tokens->type == REDIRECT_OUT || tokens->type == APPEND_IN 
			|| tokens->type == APPEND_OUT || tokens->type == NOT_SKIP))
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
	else
		return (0);
}
