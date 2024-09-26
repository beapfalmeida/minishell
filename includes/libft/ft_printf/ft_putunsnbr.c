/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:02:13 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/05/08 16:34:47 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	countnum(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_itoa(unsigned int n)
{
	int				len;
	char			*str;
	unsigned long	num;

	num = (unsigned long) n;
	len = countnum(num);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (num == 0)
		str[0] = '0';
	str[len] = '\0';
	while (num != 0 && len--)
	{
		str[len] = (num % 10) + 48;
		num = num / 10;
	}
	return (str);
}

int	ft_putunsnbr(unsigned int nb)
{
	char	*str;
	int		i;

	str = ft_itoa(nb);
	i = ft_putstr(str);
	free(str);
	return (i);
}
