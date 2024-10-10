#include "minishell.h"

static int	check_echo(t_tokens *token)
{
	if (ft_strncmp(token->token, "env", 4) != 0)
	{
		printf(get_error(ERROR_CMD), token->token);
		return (1);
	}
	return (0);
}

int	ft_echo(t_tokens *token)
{
	t_tokens	*temp;

	temp = token;
	temp = temp->next;
	if (check_echo(token))
		return (1);
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
