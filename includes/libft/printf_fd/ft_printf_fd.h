/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:28:43 by jsobreir          #+#    #+#             */
/*   Updated: 2024/05/06 16:25:00 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

# include "stdarg.h"
# include <unistd.h>
# include <stdio.h>

int		ft_printf_fd(int fd, const char *format, ...);
int		ft_putchar(char c, int fd);
int		ft_putstr(char *str, int fd);
int		ft_putnbr(int nbr, int fd);
int		ft_putpointer(unsigned long nbr, int fd);
int		ft_puthexadecimal(unsigned long nbr, char *base, int fd);
int		ft_putunsignednbr(unsigned int nbr, int fd);

#endif