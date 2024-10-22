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
	if ((*temp)->next)
		(*temp)->next->type = INPUT;
	else
	{
		(*temp)->type = BAD_SYNTAX;
		(*temp) = (*temp)->next;
		return ;
	}
	if (((*temp)->prev && ((*temp)->prev->type == CMD || (*temp)->prev->type == INPUT)))
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
	if ((*temp)->next)
		(*temp)->next->type = OUTPUT;
	else
	{
		(*temp)->type = BAD_SYNTAX;
		(*temp) = (*temp)->next;
		return ;
	}
	(*temp) = (*temp)->next->next;
	loop_assigning(temp, ARG);
}

void	append_out(t_tokens **temp)
{
	(*temp)->type = APPEND_OUT;
	if ((*temp)->next)
		(*temp)->next->type = OUTPUT;
	else
	{
		(*temp)->type = BAD_SYNTAX;
		(*temp) = (*temp)->next;
		return ;
	}
	(*temp) = (*temp)->next->next;
}

void	append_in(t_tokens **temp)
{
	(*temp)->type = APPEND_IN;
	if ((*temp)->next)
		(*temp)->next->type = LIMITER;
	else
	{
		(*temp)->type = BAD_SYNTAX;
		(*temp) = (*temp)->next;
		return ;
	}
	(*temp) = (*temp)->next->next;
}

void	command(t_tokens **temp)
{
	(*temp)->type = CMD;
	(*temp) = (*temp)->next;
	loop_assigning(temp, ARG);
}