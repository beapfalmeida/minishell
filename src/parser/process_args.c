#include "minishell.h"

int	get_input(t_tokens **tokens)
{
	t_tokens	*temp;
	char		infile;
	int			has_infile;
	int			fd;

	temp = *tokens;
	has_infile = 0;
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
		return(0);
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
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	badopen(fd, outfile);
	return (fd);
}

void	create_array(t_tokens **tokens, t_shell *args)
{
	t_tokens *temp;
	int	j;
	int i;

	temp = *tokens;
	j = 0;
	i = 0;
	while (temp)
	{
		if (temp->type == CMD || temp->type == ARG)
		{
			args->cmds[j][i] = strdup(temp->token);
			i++;
		}
		else if (temp->type == PIPE)
		{
			j++;
			i = 0;
		}
		temp = temp->next;
	}
}

t_shell	*process_tokens(t_tokens **tokens)
{
	t_shell args;

	args.fd_in = get_input(tokens);
	args.fd_out = get_output(tokens);
	args.n_pipes = count_pipes(tokens);
	args.cmds = malloc((args.n_pipes + 1) * sizeof(char **) + 1);
	create_array(tokens, &args);
	return (&args);
}
