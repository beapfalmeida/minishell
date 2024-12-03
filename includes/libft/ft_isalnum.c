/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:48:09 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/12/03 10:47:19 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>

/// @brief checks if c is alfanumeric
/// @return 1 if c is alfanumeric, 0 if it is not
int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || ((c > 64 && c < 91) || (c > 96 && c < 123))
		|| c == '_')
		return (1);
	else
		return (0);
}
