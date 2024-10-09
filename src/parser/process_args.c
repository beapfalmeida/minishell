#include "minishell.h"

void	badopen(int fd, char *file)
{
	if (fd == -1)
		printf("No such file or directory: %s\n", file);
}
void	find_limiter(t_tokens **tokens)
{
	int	fd[2];
	t_tokens	*temp;
	char	*limiter = NULL;
	char	*input_buff = NULL;
	char	*tem;

	temp = *tokens;
	while (temp)
	{
		if (temp->type == LIMITER)
		{
			limiter = temp->token;
			break ;
		}
		temp = temp->next;
	}
	if (limiter)
	{
		pipe(fd);
		limiter = ft_strjoin(limiter, "\n");
		while (1)
		{
			input_buff = readline("> ");
			tem = input_buff;
			input_buff = ft_strjoin(input_buff, "\n");
			free(tem);
			write(fd[1], input_buff, ft_strlen(input_buff));
			if (!strncmp(input_buff, limiter, ft_strlen(input_buff)))
				break ;
			free(input_buff);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	free(limiter);
	free(input_buff);
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
	{
		//find_limiter(tokens);
		return (STDIN_FILENO);
	}
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

void	process_tokens(t_tokens **tokens, t_shell *args)
{
	args->fd_in = get_input(tokens);
	args->fd_out = get_output(tokens);
	args->n_pipes = count_pipes(tokens);
}
