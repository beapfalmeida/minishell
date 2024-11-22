/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:45:29 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/20 15:57:09 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Return type of symbol.
/// @param tokens Pointer to a struct containing tokens list.
/// @param len Length of token.
/// @return 
int	is_symbol(char *token, int len)
{
	if (!ft_strncmp(token, "|", len))
		return (PIPE);
	if (!ft_strncmp(token, "<", len))
		return (REDIRECT_IN);
	if (!ft_strncmp(token, ">", len))
		return (REDIRECT_OUT);
	if (!ft_strncmp(token, ">>", len))
		return (APPEND_OUT);
	if (!ft_strncmp(token, "<<", len))
		return (1);
	return (0);
}

/// @brief Assigns Pipe type to token, and respective errors 
/// case no token before or after pipe.
/// @param temp Pointer to a struct containing tokens list.
/// @return 
static int	assign_pipe(t_tokens **temp)
{
	(*temp)->type = PIPE;
	if (!(*temp)->next && (*temp)->prev)
		return (ERROR_UNCLP);
	if (!(*temp)->prev)
		return (ERROR_PIPE);
	(*temp) = (*temp)->next;
	return (0);
}

/// @brief Assign type to each token.
/// @param temp Pointer to the tokens list.
/// @return 
static int	assign_type(t_tokens **temp)
{
	int	res;

	if ((*temp)->type == SKIP || (*temp)->type == NOT_SKIP)
		(*temp) = (*temp)->next;
	else if (!ft_strncmp((*temp)->token, "|", ft_strlen((*temp)->token))
		&& (*temp)->expanded == false)
	{
		res = assign_pipe(&(*temp));
		if (res)
			return (res);
	}
	else if ((*temp)->type == INPUT && !(*temp)->next)
		return (1);
	else if (!ft_strncmp((*temp)->token, ">", 1) && (*temp)->expanded == false)
		append_out(&(*temp));
	else if (!ft_strncmp((*temp)->token, "<", 1) && (*temp)->expanded == false)
		append_in(&(*temp));
	else if (((*temp)->prev
			&& ((*temp)->prev->type == PIPE || (*temp)->prev->type == OUTPUT)))
		command(&(*temp));
	else if (!(*temp)->prev)
		check_dir_cmd(&(*temp));
	else if ((*temp)->type != INPUT)
		loop_assigning(&(*temp), ARG);
	return (0);
}

/// @brief Iterates throut tokens list to assign a type to each.
/// @param tokens Pointer to tokens list.
/// @return 
int	assign_types(t_tokens **tokens)
{
	t_tokens	*temp;
	int			res;

	temp = *tokens;
	while (temp)
	{
		res = assign_type(&temp);
		if (res && res != 1)
			return (res);
		else if (res == 1)
			break ;
	}
	return (0);
}

/// @brief Create tokens list.
/// @param tokens Pointer to a pointer containing the tokens struct.
/// @param input 
void	create_tokens(t_tokens **tokens, char *input)
{
	char		**arr;
	int			i;
	t_tokens	*item;

	i = 0;
	arr = ft_split_adapted(input);
	if (!arr || !*arr)
		return ;
	while (arr[i])
	{
		item = new_node(arr[i], 0);
		add_back_list(tokens, item);
		i++;
	}
	free(arr);
}
