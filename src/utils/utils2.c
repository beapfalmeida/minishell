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
	temp = temp->next;
	count = 1;
	while (temp && temp->type == ARG)
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

int	find_quote(char *str)
{
	if (*str == '\"')
		return (1);
	else if (*str == '\'')
		return (2);
	return (0);
}