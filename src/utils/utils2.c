#include "minishell.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

int	count_args(t_tokens *token)
{
	t_tokens	*temp;
	int			count;

	temp = token;
	count = 1;
	while (temp && (temp->type == ARG || temp->type == CMD))
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	free_array(char	**arr, int	len)
{
	while (arr[len])
	{
		free(arr[len]);
		len--;
	}
	free(arr);
	return (0);
}

void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell && shell->cmds && *(shell->cmds))
	{
		while (shell->cmds[i])
		{
			free_array(shell->cmds[i], arr_len(shell->cmds[i]));
			i++;
		}
		free(shell->cmds);
	}
}
