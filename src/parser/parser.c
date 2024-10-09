#include "minishell.h"

int	is_symbol(char *token)
{
	if (!ft_strncmp(token, "|", ft_strlen(token)))
		return (PIPE);
	if (!ft_strncmp(token, "<", ft_strlen(token)))
		return (REDIRECT_IN);
	if (!ft_strncmp(token, ">", ft_strlen(token)))
		return (REDIRECT_OUT);
	if (!ft_strncmp(token, ">>", ft_strlen(token)))
		return (APPEND_OUT);
	if (!ft_strncmp(token, "<<", ft_strlen(token)))
		return (1);
	return (0);
}

void	assign_types(t_tokens **tokens)
{
	t_tokens	*temp;

	temp = *tokens;
	while (temp)
	{
		if (!ft_strncmp(temp->token, "|", ft_strlen(temp->token)))
		{
			temp->type = PIPE;
			temp = temp->next;
		}
		else if (!ft_strncmp(temp->token, ">", ft_strlen(temp->token)))
			redirect_out(&temp);
		else if (!ft_strncmp(temp->token, "<", ft_strlen(temp->token)))
			redirect_in(&temp);
		else if (!ft_strncmp(temp->token, ">>", ft_strlen(temp->token)))
			append_out(&temp);
		else if (!ft_strncmp(temp->token, "<<", ft_strlen(temp->token)))
			append_in(&temp);
		else if ((temp->prev && (temp->prev->type == PIPE || temp->prev->type == OUTPUT)) || !temp->prev)
			command(&temp);
		else
			loop_assigning(&temp, ARG);
	}
}

void	create_tokens(t_tokens **tokens, char *input)
{
	char		**arr;
	int			i;
	t_tokens	*item;

	i = 0;
	arr = ft_split_adapted(input);
	if (!arr || !*arr)
	{
		// if (*arr)
		// 	free(*arr);
		return ;
	}
	while (arr[i])
	{
		item = new_node(arr[i]);
		add_back_list(tokens, item);
		i++;
	}
	free_array(arr, arr_len(arr));
	assign_types(tokens);
}
