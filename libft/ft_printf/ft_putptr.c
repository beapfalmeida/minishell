/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:02:09 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/05/08 16:33:57 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	counthex(unsigned long n)
{
	int	count;

	count = 0;
	while (n)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

static int	ft_putptrhex(unsigned long n)
{
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
	{
		ft_putptrhex(n / 16);
		ft_putptrhex(n % 16);
	}
	else
		ft_putchar(base[n]);
	return (counthex(n));
}

int	ft_putptr(void *ptr)
{
	unsigned long	n;
	int				result;

	result = 0;
	n = (unsigned long)ptr;
	if (!n)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	result += ft_putstr("0x");
	if (n == 0)
		result += ft_putchar('0');
	else
		result += ft_putptrhex(n);
	return (result);
}
