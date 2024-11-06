#include "minishell.h"

t_fds	*find_last_fds(t_fds *lst)
{
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	add_back_fds(t_fds **lst, t_fds *new)
{
	t_fds	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = find_last_fds(*lst);
	last -> next = new;
}

t_fds	*new_fds(int in, int out, int i)
{
	t_fds	*node;

	node = malloc(sizeof(t_tokens));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->in = in;
	node->out = out;
	node->pn = i;
	return (node);
}
