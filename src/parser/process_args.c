#include "minishell.h"

static int	open_file(t_tokens *tokens, t_shell *shell)
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

int	get_output(t_tokens *temp, t_shell *shell, int *fd)
{
	char		*outfile;

	outfile = NULL;
	if (temp->type == OUTPUT)
	{
		outfile = temp->token;
		if (temp->prev->type == REDIRECT_OUT)
			fd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd[1] = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd[1] == -1)
		{
			if (errno == EACCES)
				do_error(temp, shell, ERROR_PDN);
			else if (errno == ENOENT)
				do_error(temp, shell, ERROR_OPEN);
			return (1);
		}
	}
	return (0);
}

int	get_input(t_tokens *temp, t_shell *shell, t_tokens *infile, int *fd)
{
	if (temp->type == INPUT)
	{
		infile = temp;
		fd[0] = open_file(infile, shell);
		if (fd[0] == -1)
		{
			//fd[0] = -1;
			close(shell->original_stdin);
			return (1);
		}
	}
	return (0);
}
int	*init_fds()
{
	int	*fd;

	fd = malloc(sizeof(int) * 2);
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	return (fd);
}

int	*get_fds(t_tokens **tokens, t_shell *shell)
{	
	int			*fd;
	t_tokens	*temp;
	t_tokens	*infile;
	int			stop;

	temp = *tokens;
	fd = init_fds();
	infile = NULL;
	stop = 0;
	while (temp)
	{
		find_limiter(temp, shell, fd);
		if (get_output(temp, shell, fd) && !stop)
			stop = 1;
		if (get_input(temp, shell, infile, fd) && !stop)
			stop = 1;
		if (temp->type == PIPE || !temp->next)
			break ;
		temp = temp->next;
	}
	return (fd);
}

void	create_fds(t_shell *args, t_tokens *tokens)
{
	int	i;
	int	fd_in;
	int	fd_out;
	int	*fd;
	t_fds		*node;
	t_fds		*fds = NULL;

	i = 0;
	fd_in = 0;
	fd_out = 0;
	while (i <= args->n_pipes)
	{
		fd = get_fds(&tokens, args);
		fd_out = fd[1];
		fd_in = fd[0];
		free(fd);
		node = new_fds(fd_in, fd_out, i);
		add_back_fds(&fds, node);
		set_next_pipe(&tokens);
		i++;
	}
	args->fds = fds;
}

int	process_tokens(t_tokens **tokens, t_shell *args)
{
	t_tokens	*temp;

	temp = *tokens;
	args->n_pipes = count_pipes(tokens);
	create_fds(args, temp);
	return (0);
}
