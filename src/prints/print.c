#include "minishell.h"

void	print_tokens(t_tokens **begin_list)
{
	t_tokens *cur = *begin_list;
	while (cur != 0)
	{
		printf("%s: type", cur->token);
		printf(" %d\n", (int)(cur->type));
		cur = cur->next;
	}
}

void	print_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		printf("arr[%i] = %s\n", i, arr[i]);
		i++;
	}
}
