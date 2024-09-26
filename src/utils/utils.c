#include "minishell.h"

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

t_tokens	*new_node(char *content)
{
	t_tokens	*node;

	node = malloc(sizeof(t_tokens));
	if (!node)
		return (NULL);
	node->token = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	lstclear(t_tokens **lst)
{
	t_tokens	*temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		temp = *lst;
		*lst = (*lst)->next;
		temp->token = 0;
		temp->type = 0;
		free(temp);
	}
}
