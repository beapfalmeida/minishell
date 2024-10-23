#include "minishell.h"

static void	set_them_free(int *pipe_fd, char *limiter, char *input_buff)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	free(limiter);
	free(input_buff);
}
static int	do_heredoc(int *pipe_fd, char *input_buff, char *limiter)
{
	input_buff = readline("> ");
	if (input_buff)
		input_buff = ft_strjoin(input_buff, "\n");
	if (!strncmp(input_buff, limiter, ft_strlen(input_buff)))
		return (1);
	write(pipe_fd[1], input_buff, ft_strlen(input_buff));
	free(input_buff);
	return (0);
}

int	find_limiter(t_tokens **tokens, t_shell *shell)
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
			limiter[++i] = '\0';
			pipe(pipe_fd);
			limiter = ft_strjoin(limiter, "\n");
			while (1)
				if(do_heredoc(pipe_fd, input_buff, limiter) == 1)
					break ;
			set_them_free(pipe_fd, limiter, input_buff);
		}
		temp = temp->next;
	}
	return (STDIN_FILENO);
}