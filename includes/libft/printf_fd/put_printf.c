/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_printf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:28:14 by jsobreir          #+#    #+#             */
/*   Updated: 2024/05/06 16:26:43 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstr(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return (write(fd, "(null)", 6));
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnbr(int nbr, int fd)
{
	int	len;

	len = 0;
	if (nbr == -2147483648)
		return (write(fd, "-2147483648", 11));
	else if (nbr < 0)
	{
		len += write(fd, "-", 1);
		len += ft_putnbr(-nbr, fd);
	}
	else if (nbr >= 10)
	{
		len += ft_putnbr(nbr / 10, fd);
		len += ft_putnbr(nbr % 10, fd);
	}
	else
	{
		nbr += '0';
		len += write(fd, &nbr, 1);
	}
	return (len);
}

int	ft_putunsignednbr(unsigned int nbr, int fd)
{
	int	len;

	len = 0;
	if (nbr >= 10)
	{
		len += ft_putnbr(nbr / 10, fd);
		len += ft_putnbr(nbr % 10, fd);
	}
	else
	{
		nbr += '0';
		len += write(fd, &nbr, 1);
	}
	return (len);
}
