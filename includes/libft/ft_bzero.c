/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:47:12 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/06/17 16:00:58 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief sets the first n values of the memory space pointed by s to '\0'
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*arr;
	unsigned int	i;

	arr = s;
	i = 0;
	while (i < n)
	{
		arr[i] = '\0' ;
		i++;
	}
}
