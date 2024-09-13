/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:28:14 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/05/08 16:33:33 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	countnum(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	num;

	num = n;
	len = countnum(num);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (num == 0)
		str[0] = '0';
	str[len] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num != 0 && len--)
	{
		str[len] = (num % 10) + 48;
		num = num / 10;
	}
	return (str);
}

int	ft_putnbr(int nb)
{
	char	*str;
	int		i;

	str = ft_itoa(nb);
	i = ft_putstr(str);
	free(str);
	return (i);
}
