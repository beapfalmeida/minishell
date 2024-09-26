#include "minishell.h"

void	init_tokens(t_tokens *tokens)
{
	tokens->token = 0;
	tokens->type = 0;
	tokens->prev = NULL;
	tokens->next = NULL;
}