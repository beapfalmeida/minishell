/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:47:21 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/06/17 17:13:40 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/// @brief Allocates memory for ann array of n elements and of size bytes
void	*ft_calloc(size_t n, size_t size)
{
	void	*arr;

	if ((n > 2147483647 && size != 0)
		|| (size > 2147483647 && n != 0))
		return (0);
	arr = malloc(n * size);
	if (!arr)
		return (0);
	ft_bzero(arr, size * n);
	return (arr);
}
