/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:47:19 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/06/17 16:24:23 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

/// @brief Creats a substring that begins at index st and is of maximum size n
/// @return The substring
char	*ft_substr(char const *str, unsigned int st, size_t n)
{
	char				*sub;
	unsigned int		len;
	char				*pst;

	if (!str)
		return (NULL);
	if (st >= ft_strlen(str))
		return (ft_strdup(""));
	pst = (char *)str + st;
	if (ft_strlen(pst) < n)
		len = ft_strlen(pst) + 1;
	else
		len = n + 1;
	sub = malloc(len * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, pst, len);
	return (sub);
}
