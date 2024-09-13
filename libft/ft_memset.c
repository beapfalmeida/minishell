/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:57:36 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/08/13 16:38:35 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h> 
#include <string.h> 

/// @brief Fills the first n bytes of the memory 
///area pointed to by s with the constant byte c
void	*ft_memset(void	*s, int c, size_t n)
{
	unsigned char	*arr;
	unsigned int	i;

	arr = s;
	i = 0;
	while (i < n)
	{
		arr[i] = c;
		i++;
	}
	return (s);
}
