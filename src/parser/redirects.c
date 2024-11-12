#include "minishell.h"

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
			close(shell->original_stdin);
			return (1);
		}
	}
	return (0);
}