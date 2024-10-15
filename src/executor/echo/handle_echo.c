#include "minishell.h"

static int	check_echo(t_tokens *tokens, t_shell *shell)
{
	if (ft_strncmp(tokens->token, "env", 4) != 0)
	{
		do_error(tokens, shell, ERROR_CMD);
		return (1);
	}
	return (0);
}

int	ft_echo(t_tokens *tokens, t_shell *shell)
{
	t_tokens	*temp;

	temp = tokens;
	temp = temp->next;
	if (check_echo(tokens, shell))
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
