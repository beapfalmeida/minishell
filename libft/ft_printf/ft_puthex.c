/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:02:03 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/05/08 16:33:02 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	counthex(unsigned long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	while (n)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

int	ft_puthex(unsigned long n, char c)
{
	char	*base_up;
	char	*base_low;

	base_up = "0123456789ABCDEF";
	base_low = "0123456789abcdef";
	if (n >= 16)
	{
		ft_puthex(n / 16, c);
		ft_puthex(n % 16, c);
	}
	else
	{
		if (c == 'x')
			ft_putchar(base_low[n]);
		if (c == 'X')
			ft_putchar(base_up[n]);
	}
	return (counthex(n));
}
