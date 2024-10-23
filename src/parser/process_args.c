#include "minishell.h"

static int	find_limiter(t_tokens **tokens, t_shell *shell)
{
	t_tokens	*temp;
	char		*limiter = NULL;
	char		*input_buff = NULL;
	int			pipe_fd[2];
	size_t		i;

	temp = *tokens;
	while (temp)
	{
		if (temp->type == LIMITER)
		{
			dup2(shell->original_stdin, STDIN_FILENO);
			limiter = malloc((ft_strlen(temp->token) + 2) * sizeof(char));
			i = 0;
			while (i < ft_strlen(temp->token))
			{
				limiter[i] = temp->token[i];
				i++;
			}
			limiter[i] = '\n';
			i++;
			limiter[i] = '\0';
			pipe(pipe_fd);
			while (1)
			{
				input_buff = readline("> ");
				if (input_buff)
					input_buff = ft_strjoin(input_buff, "\n");
				if (!strncmp(input_buff, limiter, ft_strlen(input_buff)))
					break ;
				write(pipe_fd[1], input_buff, ft_strlen(input_buff));
				free(input_buff);
			}
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			free(limiter);
			free(input_buff);
		}
		temp = temp->next;
	}
	return (STDIN_FILENO);
}

int	get_input(t_tokens **tokens, t_shell *shell)
{
	t_tokens	*temp;
	char		*infile;
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
			infile = temp->token;
			has_infile = 1;
		}
		temp = temp->next;
	}
	if (find_limiter(tokens, shell) != shell->original_stdin && has_infile)
	{
		fd = open(infile, O_RDONLY);
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

void	process_tokens(t_tokens **tokens, t_shell *args)
{
	args->fd_in = get_input(tokens, args);
	args->fd_out = get_output(tokens);
	args->n_pipes = count_pipes(tokens);
}
