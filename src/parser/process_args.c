#include "minishell.h"

void	badopen(int fd, char *file)
{
	if (fd == -1)
		printf("No such file or directory: %s\n", file);
}

int	get_input(t_tokens **tokens)
{
	t_tokens	*temp;
	char		*infile;
	int			has_infile;
	int			fd;

	temp = *tokens;
	has_infile = 0;
	infile = NULL;
	while (temp)
	{
		if (temp->type == INPUT)
		{
			infile = temp->token;
			has_infile = 1;
		}
		temp = temp->next;
	}
	if (has_infile == 0)
		return (STDIN_FILENO);
	else
	{
		fd = open(infile, O_RDONLY);
		badopen(fd, infile);
		return (fd);
	}
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
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		badopen(fd, outfile);
		return (fd);
	}
	else
		return (STDOUT_FILENO);
}

void	process_tokens(t_tokens **tokens, t_shell *args, char **envp)
{
	args->envp = envp;
	args->fd_in = get_input(tokens);
	args->fd_out = get_output(tokens);
	args->n_pipes = count_pipes(tokens);
}
