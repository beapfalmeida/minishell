/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:06:18 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/11/13 12:31:54 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/// @brief checks char by char in the string 
///set to see if they match with c
static int	check(char const *set, char c)
{
	int	j;

	j = 0;
	while (set[j])
	{
		if (set[j] == c)
			return (1);
		j++;
	}
	return (0);
}

/// @brief Makes a copy of s and removes the characters 
///specified in ’set’ from the beginning and the end of it
/// @return The new trimmed string
char	*ft_strtrim(char const *s, char const *set)
{
	unsigned int	st;
	char			*trim;
	int				e;

	st = 0;
	e = ft_strlen(s) - 1;
	while (s[st] && check(set, s[st]))
		st++;
	while (e >= 0 && check(set, s[e]))
		e--;
	trim = ft_substr(s, st, e - st + 1);
	return (trim);
}
