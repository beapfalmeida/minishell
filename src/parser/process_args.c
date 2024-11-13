#include "minishell.h"

int	open_file(t_tokens *tokens, t_shell *shell)
{
	int	fd;

	fd = open(tokens->token, O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			do_error(tokens, shell, ERROR_PDN);
		else if (errno == ENOENT)
			do_error(tokens, shell, ERROR_OPEN);
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

static void	create_fds(t_shell *args, t_tokens *tokens, int fd_in, int fd_out)
{
	int		*fd;
	int		i;
	t_fds	*node;

	args->fds = NULL;
	i = 0;
	while (i <= args->n_pipes)
	{
		fd = get_fds(&tokens, args);
		fd_out = fd[1];
		fd_in = fd[0];
		free(fd);
		node = new_fds(fd_in, fd_out, i);
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
	create_fds(args, temp, 0, 0);
	return (0);
}
