/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:50:45 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/06/17 16:11:53 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

/// @brief Concatenates s1 with s2
/// @return The concatenated string
char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	tlen;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tlen = ft_strlen(s1) + ft_strlen(s2);
	new = malloc((tlen + 1) * sizeof(char));
	if (!new)
		return (0);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
