#include "minishell.h"

static void	se_them_free(int *pipe_fd, char *limiter, char *input_buff)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	free(limiter);
	free(input_buff);
}
static int	do_hereoc(int *pipe_fd, char *input_buff, char *limiter)
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

static int	find_limiter(t_tokens **tokens, t_shell *shell)
{
	t_tokens	*temp;
	char		*limiter = NULL;
	char		*input_buff = NULL;
	int			pipe_fd[2];

	temp = *tokens;
	while (temp)
	{
		if (temp->type == LIMITER)
		{
			dup2(shell->original_stdin, STDIN_FILENO);
			limiter = ft_strdup(temp->token);
			pipe(pipe_fd);
			limiter = ft_strjoin(limiter, "\n");
			while (1)
			{
				if(do_heredoc(pipe_fd, input_buff, limiter) == 1)
					break ;
			}
			set_them_free(pipe_fd, limiter, input_buff);
		}
		temp = temp->next;
	}
	return (STDIN_FILENO);
}
