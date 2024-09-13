/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:32:41 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/06/16 10:14:22 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strclen_gnl(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	*ft_strdup_gnl(char *src, int size)
{
	char	*new;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (!new)
		return (0);
	while (i < size)
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*new;
	size_t	tlen;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tlen = ft_strclen_gnl(s1, '\0') + ft_strclen_gnl(s2, '\0');
	new = malloc((tlen + 1) * sizeof(char));
	if (!new)
		return (0);
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(s1);
	return (new);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (s[i] == (char)c)
		return ((char *)s);
	else
		return (NULL);
}
