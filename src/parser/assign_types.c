#include "minishell.h"

void	loop_assigning(t_tokens **temp, int type)
{
	while ((*temp) && !is_symbol((*temp)->token))
	{
		(*temp)->type = type;
		(*temp) = (*temp)->next;
	}
}
void	redirect_in(t_tokens **temp)
{
	(*temp)->type = REDIRECT_IN;
	(*temp)->next->type = INPUT;
	if (((*temp)->prev && (*temp)->prev->type == CMD))
	{
		(*temp) = (*temp)->next->next;
		loop_assigning(temp, INPUT);
	}
	else
	{
		(*temp) = (*temp)->next->next;
		command(temp);
	}
}

void	redirect_out(t_tokens **temp)
{
	(*temp)->type = REDIRECT_OUT;
	(*temp)->next->type = OUTPUT;
	(*temp) = (*temp)->next->next;
	loop_assigning(temp, ARG);
}

void	append_out(t_tokens **temp)
{
	(*temp)->type = APPEND_OUT;
	(*temp)->next->type = OUTPUT;
	(*temp) = (*temp)->next->next;
}

void	append_in(t_tokens **temp)
{
	(*temp)->type = APPEND_IN;
	(*temp)->next->type = LIMITER;
	(*temp) = (*temp)->next->next;
}

void	command(t_tokens **temp)
{
	(*temp)->type = CMD;
	(*temp) = (*temp)->next;
	loop_assigning(temp, ARG);
}