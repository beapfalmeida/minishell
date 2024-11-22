/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:46:28 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/20 15:46:29 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_tokens **tokens)
{
	t_tokens	*temp;
	int			count;

	temp = *tokens;
	count = 0;
	while (temp)
	{
		if (temp->type == PIPE)
			count++;
		temp = temp->next;
	}
	return (count);
}

t_tokens	*find_last(t_tokens *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	add_back_list(t_tokens **lst, t_tokens *new)
{
	t_tokens	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = find_last(*lst);
	last -> next = new;
	new -> prev = last;
}

t_tokens	*new_node(char *content, int type)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (!node)
		return (NULL);
	node->token = content;
	node->type = type;
	node->expanded = false;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	lstclear(t_tokens **lst, int clean)
{
	t_tokens	*temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		if (temp->token && clean)
			free(temp->token);
		temp->type = 0;
		free(temp);
	}
}
