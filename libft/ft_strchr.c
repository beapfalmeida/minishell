/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:02:20 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/08/13 16:40:00 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

/// @brief Scans the string pointed to by s for the first instance of c
/// @return A pointer to the first appearance of c in s, 
///or NULL if the char is not found
char	*ft_strchr(const char *s, int c)
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
