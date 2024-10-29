/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hexptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:36:36 by jsobreir          #+#    #+#             */
/*   Updated: 2024/05/05 19:58:57 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	ft_puthexadecimal(unsigned long nbr, char *base, int fd)
{
	int		len;

	len = 0;
	if (nbr >= 16)
	{
		len += ft_puthexadecimal(nbr / 16, base, fd);
		len += ft_puthexadecimal(nbr % 16, base, fd);
	}
	else
		len += write(fd, &base[nbr], 1);
	return (len);
}

int	ft_putpointer(unsigned long nbr, int fd)
{
	int		len;
	char	*base;

	base = "0123456789abcdef";
	len = 0;
	if (!nbr)
		len += write(fd, "(nil)", 5);
	else
	{
		len += write(fd, "0x", 2);
		len += ft_puthexadecimal(nbr, base, fd);
	}
	return (len);
}
