#include "minishell.h"

static int check_dir_cmd(t_tokens **tokens)
{
	char *token;

	token = (*tokens)->token;
	if ((*token == '.' || *token == '~' || has_char(token, '/')) && (*tokens)->type != NOT_FILE)
	{
		(*tokens)->type = DIR_FILE;
		(*tokens) = (*tokens)->next;
	}
	else
		command(tokens);
	return (0);
}

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

void	assign_types(t_tokens **tokens)
{
	t_tokens	*temp;

	temp = *tokens;
	while (temp)
	{
		if (temp->type == SKIP)
			temp = temp->next;
		else if (!ft_strncmp(temp->token, "|", ft_strlen(temp->token)))
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
		else if ((temp->prev && (temp->prev->type == PIPE || temp->prev->type == OUTPUT)))
			command(&temp);
		else if (!temp->prev)
			check_dir_cmd(&temp);
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
		item = new_node(arr[i], 0);
		add_back_list(tokens, item);
		i++;
	}
	free_array(arr, arr_len(arr));
}
