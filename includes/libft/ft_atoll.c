/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:14:26 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/13 12:44:29 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*skip_smpl(char *nptr, long long *sign)
{
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
	{
		*sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	return (nptr);
}

long long	ft_atoll(char *nptr, int *overflow)
{
	long long	result;
	long long	sign;
	long long	max_div_10;

	result = 0;
	sign = 1;
	max_div_10 = 9223372036854775807 / 10;
	nptr = skip_smpl(nptr, &sign);
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (result > max_div_10
			|| (result == max_div_10 && (*nptr - '0') > 7))
		{
			if (sign == 1)
				return (*overflow = 1, LONG_MAX);
			else
				return (*overflow = 1, LONG_MIN);
		}
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * result);
}
