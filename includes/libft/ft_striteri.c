/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:27:36 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/08/13 16:40:10 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/// @brief Applies the function ’f’ on each character 
///of the string passed as argument,
/// passing its index as first argument
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (s && f)
	{
		while (s[i])
		{
			f(i, &s[i]);
			i++;
		}
	}
}
