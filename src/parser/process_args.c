#include "minishell.h"

int	get_input(t_tokens **tokens, t_shell *shell)
{
	t_tokens	*temp;
	t_tokens	*infile;
	int			has_infile;
	int			fd;

	temp = *tokens;
	has_infile = 0;
	fd = 0;
	infile = NULL;
	while (temp)
	{
		if (temp->type == INPUT)
		{
			infile = temp;
			has_infile = 1;
		}
		temp = temp->next;
	}
	if (find_limiter(tokens, shell) != shell->original_stdin && has_infile)
	{
		fd = open(infile->token, O_RDONLY);
		if (fd == -1)
			do_error(infile, shell, ERROR_OPEN);
		return (fd);
	}
	return (STDIN_FILENO);
}

int	get_output(t_tokens **tokens)
{
	t_tokens	*temp;
	char		*outfile;
	int			fd;

	outfile = NULL;
	temp = *tokens;
	while (temp)
	{
		if (temp->type == OUTPUT)
		{
			outfile = temp->token;
			break ;
		}
		temp = temp->next;
	}
	if (outfile != NULL)
	{
		if (temp->prev->type == REDIRECT_OUT)
			fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		return (fd);
	}
	else
		return (STDOUT_FILENO);
}

int	process_tokens(t_tokens **tokens, t_shell *args)
{
	args->fd_in = get_input(tokens, args);
	if (args->fd_in == -1)
		return (1);
	args->fd_out = get_output(tokens);
	args->n_pipes = count_pipes(tokens);
	return (0);
}
