#include "minishell.h"

int	ft_echo(t_tokens *token)
{
	while (token->token && token->type == ARG)
	{
		printf("%s", token->token);
	}
	write(1, "\n", 1);
	return (0);
}
