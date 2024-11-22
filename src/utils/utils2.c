/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:46:31 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/20 15:56:45 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

int	count_args(t_tokens *token)
{
	t_tokens	*temp;
	int			count;

	temp = token;
	count = 1;
	while (temp && (temp->type == ARG || temp->type == CMD
			|| temp->type == DIR_FILE))
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	free_array(char	**arr, int len)
{
	while (arr[len])
	{
		free(arr[len]);
		len--;
	}
	free(arr);
	return (0);
}

char	**ft_arrdup(char **arr)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc((arr_len(arr) + 1) * sizeof(char *));
	while (arr && *arr)
	{
		ret[i] = ft_strdup(*arr);
		i++;
		arr++;
	}
	ret[i] = NULL;
	return (ret);
}

int	ft_strclen(char *str, char c)
{
	int	len;

	len = 0;
	while (str && *str && *str != c)
	{
		str++;
		len++;
	}
	return (len);
}
