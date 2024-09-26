/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:01:41 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/05/02 11:01:41 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

int		ft_printf(const char *s, ...);
int		ft_putstr(char *str);
int		ft_putnbr(int nb);
int		ft_putchar(char c);
int		ft_puthex(unsigned long n, char c);
size_t	ft_strlen(const char *str);
int		ft_putptr(void *ptr);
int		ft_putunsnbr(unsigned int nb);

#endif
