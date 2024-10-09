#include "minishell.h"

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

int	countwords(char *s, int j, int count)
{
	int	i;

	i = j;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (s[i] == '|')
		{
			i++;
			count++;
		}
		else if (s[i] && s[i] != ' ' && s[i] != '|')
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
//TODO: melhorar esta cena - e capaz de estar errado - isto so afeta leaks
int	ft_word_len(char *s, int i)
{
	int count;
	int	j = i;

	count = 1;
	while (s[j])
	{
		while (s[j] && s[j] == ' ')
			j++;
		if (s[j] && s[j] == '\"')
		{
			j++;
			while (s[j] && s[j] != '\"')
				j++;
		}
		if (s[j] && s[j] == '\'')
		{
			j++;
			while (s[j] && s[j] != '\'')
				j++;
		}
		while (s[j] && s[j] != ' ' && s[j] != '|' && s[j] != '\"' && s[j] != '\'')
				j++;
		if (s[j] && s[j] == '|') 
		{
			count++;
			j++;
		}
		if (s[j] && s[j] == ' ')
			count++;
	}
	return (count);
}
