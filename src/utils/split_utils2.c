#include "minishell.h"

void	write_char(t_split *sp)
{
	sp->arr[sp->j][sp->k++] = sp->s[sp->i++];
	sp->arr[sp->j][sp->k++] = sp->s[sp->i++];
}

void	split_quotes(t_split *sp, char c)
{
	sp->arr[sp->j][sp->k++] = sp->s[sp->i++];
	while (sp->s[sp->i] && sp->s[sp->i] != c)
		sp->arr[sp->j][sp->k++] = sp->s[sp->i++];
	sp->arr[sp->j][sp->k++] = sp->s[sp->i++];
}

int	malloc_gone_wrong(char **arr, int j)
{
	int	i;

	i = j;
	if (!arr[i])
	{
		while (i--)
			free(arr[i]);
		free(arr);
		return (1);
	}
	return (0);
}
