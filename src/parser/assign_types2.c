#include "minishell.h"

void	loop_assigning(t_tokens **temp, int type)
{
	while ((*temp) && !is_symbol((*temp)->token, ft_strlen((*temp)->token)))
	{
		(*temp)->type = type;
		(*temp) = (*temp)->next;
	}
}

void	command(t_tokens **temp)
{
	(*temp)->type = CMD;
	(*temp) = (*temp)->next;
	loop_assigning(temp, ARG);
}
