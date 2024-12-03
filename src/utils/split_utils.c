/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:46:15 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/20 15:54:32 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_inquote(char *s, int i)
{
	if (s[i] == '\'')
	{
		i++;
		while (s[i] != '\'')
		{
			if (!s[i])
				return (ft_printf_fd(2, "No support for unclosed quotes\n"), 0);
			i++;
		}
	}
	else if (s[i] == '\"')
	{
		i++;
		while (s[i] != '\"')
		{
			if (!s[i])
				return (ft_printf_fd(2, "No support for unclosed quotes\n"), 0);
			i++;
		}
	}
	return (i + 1);
}

int	check_nt(char *s)
{
	if (!ft_strncmp(s, "<<", 2) || !ft_strncmp(s, ">>", 2))
		return (1);
	if (*s == '|' || *s == '<' || *s == '>')
		return (2);
	else if (*s && *s != ' ' && ft_strncmp(s, "<<", 2)
		&& ft_strncmp(s, ">>", 2) && *s != '|' && *s != '<' && *s != '>')
		return (3);
	return (0);
}

int	while_not_symbol(char *s, int i)
{
	while (check_nt(&s[i]) == 3)
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			i = count_inquote(s, i);
			if (!i)
				return (0);
		}
		else
			i++;
	}
	return (i);
}

int	countwords(char *s, int i, int count)
{
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (check_nt(&s[i]) == 2)
		{
			i++;
			count++;
		}
		else if (check_nt(&s[i]) == 1)
		{
			i += 2;
			count++;
		}
		else if (check_nt(&s[i]) == 3)
		{
			count++;
			i = while_not_symbol(s, i);
			if (!i)
				return (0);
		}
	}
	return (count);
}

int	ft_word_len(char *s, int j)
{
	bool	dq;
	bool	sq;
	int		count;
	int		i;

	sq = false;
	dq = false;
	count = 0;
	i = j;
	while (s[i])
	{
		if (s[i] == '\'' && dq == false)
			sq = !sq;
		else if (s[i] == '\"' && sq == false)
			dq = !dq;
		else if ((s[i] == ' ' || is_symbol(&s[i], 1))
			&& sq == false && dq == false)
			break ;
		i++;
		count++;
	}
	return (count);
}
