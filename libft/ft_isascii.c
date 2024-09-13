/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 21:50:33 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/06/17 16:03:59 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @brief checks if c is ascii
/// @return 1 if c is ascii, 0 if it is not
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
