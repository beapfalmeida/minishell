#include "minishell.h"
# include <stdlib.h>

int	count_inquote(char *s, int i)
{
	if (s[i] == '\'')
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
	}
	else if (s[i] == '\"')
	{
		i++;
		while (s[i] && s[i] != '\"')
			i++;
	}
	return (i + 1);
}
static int	countwords(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i] == '|')
		{
			i++;
			count++;
		}
		else
		{
			count++;
			while (s[i] && s[i] != ' ' && s[i] != '|')
			{
				if (s[i] == '\'' || s[i] == '\"')
					i = count_inquote(s, i);
				else
					i++;
			}
		}
	}
	return (count);
}

static int	ft_word_len(char *s, int i, char c)
{
	int count;

	count = 0;
	if (c != 0)
	{
		while (s[i] && s[i] != c)
		{
			count++;
			i++;
		}
	}
	while (s[i] && (s[i] != ' ' || s[i] != '|'))
	{
		count++;
		i++;
	}
	return (count + 1);
}

static int malloc_gone_wrong(char **arr, int j)
{
	if (!arr[j])
	{
		while (j--)
			free(arr[j]);
		free(arr);
		return (1);
	}
	return (0);
}

void	split_words(char **arr, char *s, int j, int k)
{
	int i;

	i = 0;
	while (s[i])
	{
		k = 0;
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i] == '|')
		{
			arr[j] = malloc(2 * sizeof(char));
			if (malloc_gone_wrong(arr, j))
				return ;
			arr[j][k++] = s[i++];
		}
		if (s[i] == '\"')
		{
			arr[j] = malloc(ft_word_len(s, i, '\"') * sizeof(char));
			if (malloc_gone_wrong(arr, j))
				return ;
			arr[j][k++] = s[i++];
			while (s[i] != '\"')
				arr[j][k++] = s[i++];
			while (s[i] && s[i] != ' ' && s[i] != '|')
				arr[j][k++] = s[i++];
		}
		else if (s[i] == '\'')
		{
			arr[j] = malloc(ft_word_len(s, i, '\'') * sizeof(char));
			if (malloc_gone_wrong(arr, j))
				return ;
			arr[j][k++] = s[i++];
			while (s[i] != '\'')
				arr[j][k++] = s[i++];
			while (s[i] && s[i] != ' ' && s[i] != '|')
				arr[j][k++] = s[i++];
		}
		else
		{
			arr[j] = malloc(ft_word_len(s, i, 0) * sizeof(char));
			if (malloc_gone_wrong(arr, j))
				return ;
			while (s[i] && s[i] != ' ' && s[i] != '|')
				arr[j][k++] = s[i++];
		}
		arr[j][k] = '\0';
		j++;
	}
	arr[j] = 0;
}

char	**ft_split_adapted(char *s)
{
	int		n;
	char	**arr;
	int	i;
	int	j;
	int	k;

	n = countwords(s);
	i = 0;
	j = 0;
	k = 0;
	arr = (char **)malloc((n + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	split_words(arr, s, j, k);
	if (!*arr)
		return (free(arr), NULL);
	return (arr);
}
