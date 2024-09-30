#include "minishell.h"

int	ft_echo(t_tokens *token)
{
	t_tokens	*temp;

	temp = token;
	temp = temp->next;
	while (temp->token && temp->type == ARG)
	{
		printf("%s ", temp->token);
		temp = temp->next;
		if (temp == NULL)
			break ;
	}
	printf("\n");
	return (0);
}
