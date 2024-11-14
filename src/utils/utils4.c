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

t_fds	*find_redirects(t_fds *fds, int i)
{
	t_fds	*temp;

	temp = fds;
	while (temp)
	{
		if (i == temp->pn)
			return (temp);
		temp = temp->next;
	}
	return (fds);
}

int	check_exit_exec(t_tokens **tokens, t_shell *shell, char *inbuff)
{
	if (shell->interrupt_exec == true)
	{
		shell->interrupt_exec = false;
		free_all(tokens, shell, inbuff);
		return (2);
	}
	if (ft_strlen((*tokens)->token) && !ft_strncmp((*tokens)->token, "exit", 5))
	{
		if (*tokens && (*tokens)->next)
			shell->exit_code = getexitcode(*tokens, (*tokens)->next->token);
		if ((*tokens)->next->next && shell->exit_code != 2)
		{
			ft_printf_fd(2, "bash: exit: too many arguments\n");
			shell->exit_code = 1;
			lstclear(tokens, 1);
			free(inbuff);
			return (2);
		}
		else
			return (1);
	}
	return (0);
}
