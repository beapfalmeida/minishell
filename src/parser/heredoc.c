#include "minishell.h"

static void	set_them_free(int *pipe_fd, char *limiter)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	free(limiter);
}
static int	do_heredoc(int *pipe_fd, char *limiter)
{
	char	*temp;
	char	*input_buff;

	temp = NULL;
	input_buff = readline("> ");
	if (input_buff)
	{
		temp = ft_strjoin(input_buff, "\n");
		free(input_buff);
	}
	input_buff = temp;
	if (!strncmp(input_buff, limiter, ft_strlen(input_buff)))
		return (1);
	write(pipe_fd[1], input_buff, ft_strlen(input_buff));
	free(input_buff);
	return (0);
}

int	find_limiter(t_tokens **tokens, t_shell *shell)
{
	t_tokens	*temp;
	char		*limiter;
	int			pipe_fd[2];
	int			i;

	temp = *tokens;
	while (temp)
	{
		if (temp->type == LIMITER)
		{
			dup2(shell->original_stdin, STDIN_FILENO);
			limiter = malloc((ft_strlen(temp->token) + 2));
			i = 0;
			while (temp->token[i])
			{
				limiter[i] = temp->token[i];
				i++;
			}
			limiter[i] = '\n';
			i++;
			limiter[i] = '\0';
			if (pipe(pipe_fd) <= -1)
				;
			while (1)
				if(do_heredoc(pipe_fd, limiter) == 1)
					break ;
			set_them_free(pipe_fd, limiter);
		}
		temp = temp->next;
	}
	return (STDIN_FILENO);
}