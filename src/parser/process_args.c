#include "minishell.h"

static int	open_file(t_tokens *tokens, t_shell *shell)
{
	int	fd;

	fd = open(tokens->token, O_RDONLY);
	if (fd == -1)
	{
		do_error(tokens, shell, ERROR_OPEN);
		shell->exit_code = 1;
	}
	return (fd);
}

int	get_input(t_tokens **tokens, t_shell *shell)
{
	t_tokens	*temp;
	t_tokens	*infile;
	int			has_infile;

	shell->original_stdin = dup(STDIN_FILENO);
	temp = *tokens;
	has_infile = 0;
	infile = NULL;
	while (temp)
	{
		if (temp->type == INPUT)
		{
			infile = temp;
			if (open_file(infile, shell) == -1)
				return (close(shell->original_stdin), -1);
			has_infile = 1;
		}
		if (temp->type == PIPE || !temp->next)
			break ;
		temp = temp->next;
	}
	if (find_limiter(tokens, shell) != shell->original_stdin && has_infile)
	{
		close(shell->original_stdin);
		return (open_file(infile, shell));
	}
	//close(shell->original_stdin);
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
			outfile = temp->token;
		if (temp->type == PIPE || !temp->next)
			break ;
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
void	create_fds(t_shell *args, t_tokens *tokens)
{
	int	i;
	t_fds		*node;
	t_fds		*fds = NULL;

	i = 0;
	while (i <= args->n_pipes)
	{
		node = new_fds(get_input(&tokens, args), get_output(&tokens), i);
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
