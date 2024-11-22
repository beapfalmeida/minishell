/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:45:34 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/20 15:45:35 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_tokens *tokens, t_shell *shell)
{
	int	fd;

	fd = open(tokens->token, O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			do_error(0, tokens, shell, ERROR_PDN);
		else if (errno == ENOENT)
			do_error(0, tokens, shell, ERROR_OPEN);
	}
	return (fd);
}

int	*get_fds(t_tokens **tokens, t_shell *shell)
{
	int			*fd;
	t_tokens	*temp;
	t_tokens	*infile;
	int			stop;

	temp = *tokens;
	fd = init_fds(&stop, &infile);
	while (temp)
	{
		find_limiter(temp, shell, fd);
		if (!stop)
		{
			if (get_output(temp, shell, fd))
				stop = 1;
		}
		if (!stop)
		{
			if (get_input(temp, shell, infile, fd))
				stop = 1;
		}
		if (temp->type == PIPE || !temp->next)
			break ;
		temp = temp->next;
	}
	return (fd);
}

static void	create_fds(t_shell *args, t_tokens *tokens)
{
	int		*fd;
	int		i;
	t_fds	*node;

	args->fds = NULL;
	i = 0;
	while (i <= args->n_pipes)
	{
		fd = get_fds(&tokens, args);
		node = new_fds(fd[0], fd[1], i);
		free(fd);
		add_back_fds(&args->fds, node);
		set_next_pipe(&tokens);
		i++;
	}
}

int	process_tokens(t_tokens **tokens, t_shell *args)
{
	t_tokens	*temp;

	temp = *tokens;
	args->n_pipes = count_pipes(tokens);
	create_fds(args, temp);
	return (0);
}

/// @brief Checks if a topen is of DIR_FILE type.
/// @param tokens Pointer to a struct containing tokens list.
/// @return 
int	check_dir_cmd(t_tokens **tokens)
{
	char	*token;

	token = (*tokens)->token;
	if ((*token == '.' || *token == '~' || has_char(token, '/')))
	{
		(*tokens)->type = DIR_FILE;
		(*tokens) = (*tokens)->next;
	}
	else
		command(tokens);
	return (0);
}
