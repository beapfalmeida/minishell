/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_types2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:45:14 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/20 15:45:15 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_assigning(t_tokens **temp, int type)
{
	while ((*temp) && (!is_symbol((*temp)->token, ft_strlen((*temp)->token))
			|| (*temp)->expanded == true))
	{
		(*temp)->type = type;
		(*temp) = (*temp)->next;
	}
}

void	command(t_tokens **temp)
{
	(*temp)->type = CMD;
	(*temp) = (*temp)->next;
	loop_assigning(temp, ARG);
}
