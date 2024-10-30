/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:28:32 by jsobreir          #+#    #+#             */
/*   Updated: 2024/05/06 16:26:31 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

int	ft_print_format(char c, va_list args, int fd)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_putchar(va_arg(args, int), fd);
	if (c == 's')
		len += ft_putstr(va_arg(args, char *), fd);
	if (c == 'p')
		len += ft_putpointer(va_arg(args, unsigned long), fd);
	if (c == 'i' || c == 'd')
		len += ft_putnbr(va_arg(args, int), fd);
	if (c == 'u')
		len += ft_putunsignednbr(va_arg(args, unsigned int), fd);
	if (c == '%')
	{
		c = '%';
		len += write(fd, &c, 1);
	}
	if (c == 'x')
		len += ft_puthexadecimal(va_arg(args, unsigned int),
				"0123456789abcdef", fd);
	if (c == 'X')
		len += ft_puthexadecimal(va_arg(args, unsigned int),
				"0123456789ABCDEF", fd);
	return (len);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	int			len;
	va_list		args;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
			len += ft_print_format(*(++format), args, fd);
		else
		{
			write(fd, format, 1);
			len++;
		}
		format++;
	}
	va_end(args);
	return (len);
}
// int main (void)
// {
// 	printf("\n%d", ft_printf("%d", -87));
// }
// int	main()
// {
// 	char c = 'k'; // %c
// 	char *str = "String test"; // %s
// 	char *var; var = &c;// %p
// 	int	nbr = -5;// %d // %i
// 	unsigned int nbrr = 20;// %u
// 	int b= 0xffffffff;// %x // %X
// 	// %%
// 	int i;
// 	printf("Printf replica:\n");
// 	i = ft_printf("| TEST TEXT |\n| Single Char: %c |\n| String:
//  %s |\n| Pointer Adress: %p |\n| Decimal: %d |\n| Integer %i 
// |\n| Unsign deci: %u |\n| HexLower: %x |\n| HexUpper: %X |\n| 
// Percentage sign: %% |\n", c, str, var, nbr, nbr, nbrr, b, b);
// 	printf("\nReturn Value: %d", i);
// 	///////////////////////////////
// 	printf("\nPrintf original:\n");
// 	i = printf("| TEST TEXT |\n| Single Char: 
// %c |\n| String: %s |\n| Pointer Adress: %p |\n| Decimal: 
// %d |\n| Integer %i |\n| Unsign deci: %u |\n| HexLower: %x |\n| 
// HexUpper: %X |\n| Percentage sign: %% |\n", c, str, var, nbr, 
// nbr, nbrr, b, b);
// 	printf("\nReturn Value: %d", i);
// 	return (0);
// }