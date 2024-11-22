/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:45:11 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/20 15:45:12 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in(t_tokens **temp)
{
	(*temp)->type = REDIRECT_IN;
	if ((*temp)->next && !is_symbol((*temp)->next->token, 1))
		(*temp)->next->type = INPUT;
	else
	{
		(*temp)->type = ERROR_SYNTAX;
		(*temp) = (*temp)->next;
		return ;
	}
	if ((*temp)->next->next && ((*temp)->prev && ((*temp)->prev->type == CMD
				|| (*temp)->prev->type == INPUT)))
	{
		(*temp) = (*temp)->next->next;
		loop_assigning(temp, ARG);
	}
	else if ((*temp)->next->next && (*(*temp)->next->next->token != '>'
			&& *(*temp)->next->next->token != '<'))
		(*temp) = (*temp)->next->next;
	else if ((*temp)->next->next && (*(*temp)->next->next->token == '>'
			|| *(*temp)->next->next->token == '<'))
		(*temp) = (*temp)->next->next;
	else
		(*temp) = (*temp)->next;
}

void	redirect_out(t_tokens **temp)
{
	(*temp)->type = REDIRECT_OUT;
	if ((*temp)->next && !is_symbol((*temp)->next->token, 1))
		(*temp)->next->type = OUTPUT;
	else
	{
		(*temp)->type = ERROR_SYNTAX;
		(*temp) = (*temp)->next;
		return ;
	}
	(*temp) = (*temp)->next->next;
	loop_assigning(temp, ARG);
}

void	append_out(t_tokens **temp)
{
	if (!ft_strncmp((*temp)->token, ">", ft_strlen((*temp)->token)))
	{
		redirect_out(temp);
		return ;
	}
	(*temp)->type = APPEND_OUT;
	if ((*temp)->next && !is_symbol((*temp)->next->token, 1))
		(*temp)->next->type = OUTPUT;
	else
	{
		(*temp)->type = ERROR_SYNTAX;
		(*temp) = (*temp)->next;
		return ;
	}
	(*temp) = (*temp)->next->next;
}

void	append_in(t_tokens **temp)
{
	if (!ft_strncmp((*temp)->token, "<", ft_strlen((*temp)->token)))
	{
		redirect_in(temp);
		return ;
	}
	(*temp)->type = APPEND_IN;
	if ((*temp)->next && !is_symbol((*temp)->next->token, 1))
		(*temp)->next->type = LIMITER;
	else
	{
		(*temp)->type = ERROR_SYNTAX;
		(*temp) = (*temp)->next;
		return ;
	}
	(*temp) = (*temp)->next->next;
}
