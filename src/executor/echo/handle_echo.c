#include "minishell.h"

static int	check_flag(t_tokens **tokens)
{
	char *token;
	int	i;

	i = 0;
	token = (*tokens)->token;
	if (token[i++] == '-')
	{
		while (token[i] == 'n')
			i++;
		if (!token[i])
		{
			(*tokens) = (*tokens)->next;
			return (1);
		}
	}
	return (0);
}

static int	check_echo(t_tokens *tokens, t_shell *shell)
{
	if (ft_strncmp(tokens->token, "echo", 4) != 0)
	{
		do_error(tokens, shell, ERROR_CMD);
		return (1);
	}
	return (0);
}

int	ft_echo(t_tokens *tokens, t_shell *shell)
{
	t_tokens	*temp;
	int	flag;

	temp = tokens;
	temp = temp->next;
	if (check_echo(tokens, shell))
		return (1);
	flag = check_flag(&temp);
	if (flag && !(temp && temp->type == ARG))
		return (1);
	if (temp)
	while (temp->token && temp->type == ARG)
	{
		printf("%s", temp->token);
		if (temp->next && temp->next->type == ARG)
			printf(" ");
		temp = temp->next;
		if (temp == NULL)
			break ;
	}
	if (!flag)
		printf("\n");
	return (1);
}
