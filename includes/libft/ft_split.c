/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:54:39 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/08/13 16:41:25 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	countwords(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*write_word(char *arr, char *word, int pos, int len)
{
	int	i;

	i = 0;
	while (len > 0)
	{
		arr[i] = word[pos - len];
		len--;
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

static char	**free_array(char **arr, int j)
{
	while (j--)
		free(arr[j]);
	free(arr);
	return (NULL);
}

static char	**save_words(char **arr, char *s, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	while (j < countwords(s, c))
	{
		count = 0;
		while (s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			count++;
			i++;
		}
		arr[j] = malloc((count + 1) * sizeof(char));
		if (!arr[j])
			return (free_array(arr, j));
		arr[j] = write_word(arr[j], s, i, count);
		j++;
	}
	arr[j] = NULL;
	return (arr);
}

/// @brief Splits a string into multiple, delimited by c,
/// saving them in an array that is returned
char	**ft_split(char *s, char c)
{
	int		n;
	char	**arr;

	n = countwords(s, c);
	arr = (char **)malloc((n + 1) * sizeof(char *));
	if (!arr)
		return (0);
	arr = save_words(arr, s, c);
	return (arr);
}
