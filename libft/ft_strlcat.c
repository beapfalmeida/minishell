/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:03:50 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/06/17 16:14:58 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Appends the src to the end of dest
/// @return Total length of the string created up to size
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	k;
	unsigned int	dlen;
	unsigned int	slen;

	k = 0;
	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (size == 0 || size <= dlen)
		return (slen + size);
	while (src[k] && k < size - dlen - 1)
	{
		dest[dlen + k] = src[k];
		k++;
	}
	dest[dlen + k] = '\0';
	return (dlen + slen);
}
