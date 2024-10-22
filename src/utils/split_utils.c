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

int	check_new_token(char *s)
{
	if (!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">>", 2))
		return (1);
	if (*s == '|' || *s == '<' || *s == '>')
		return (2);
	else if (*s && *s != ' ' && ft_strncmp(s, "<<", 2) &&
		ft_strncmp(s, ">>", 2) && *s != '|' && *s != '<' && *s != '>')
		return (3);
	return (0);
}

int	countwords(char *s, int j, int count)
{
	int	i;

	i = j;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (check_new_token(&s[i]) == 2)
		{
			i++;
			count++;
		}
		else if (check_new_token(&s[i]) == 1)
		{
			i += 2;
			count++;
		}
		else if (check_new_token(&s[i]) == 3)
		{
			count++;
			while (check_new_token(&s[i]) == 3)
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

//TODO: change this with << and <
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

int malloc_gone_wrong(char **arr, int j)
{
	int i = j;
	if (!arr[i])
	{
		while (i--)
			free(arr[i]);
		free(arr);
		return (1);
	}
	return (0);
}
