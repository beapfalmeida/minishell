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

int	ft_word_len(char *s, int i)
{
	int count;
	int	j = i;

	count = 0;	
	while (s[j] && s[j] == ' ')
		j++;
	while (s[j])
	{
		if (s[j] == '\'')
		{
			j++;
			count++;
			while (s[j] && s[j] != '\'')
			{
				count++;
				j++;
			}
			count++;
			j++;
		}
		if (s[j] == '\"')
		{
			j++;
			count++;
			while (s[j] && s[j] != '\"')
			{
				count++;
				j++;
			}
			j++;
			count++;
		}
		while (s[j] && s[j] != '\"' && s[j] != '\'' && s[j] != ' ' && s[j] != '|')
		{
			count++;
			j++;
		}
		if (s[j] == ' ' || s[j] == '|')
			break ;
	}
	return (count + 1);
}
