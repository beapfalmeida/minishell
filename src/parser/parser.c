#include "minishell.h"

static int	has_bars(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static int check_dir_cmd(t_tokens **tokens)
{
	char *token;

	token = (*tokens)->token;
	if (*token == '.' || *token == '~' || has_bars(token))
	{
		(*tokens)->type = DIR_FILE;
		(*tokens) = (*tokens)->next;
	}
	else
		command(tokens);
	return (0);
}

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
		else if ((temp->prev && (temp->prev->type == PIPE || temp->prev->type == OUTPUT)))
			command(&temp);
		else if (!temp->prev)
		{
			if (check_dir_cmd(&temp))
				break ;
		}
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
}
