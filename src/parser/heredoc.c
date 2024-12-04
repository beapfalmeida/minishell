/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:45:25 by jsobreir          #+#    #+#             */
/*   Updated: 2024/12/04 12:15:56 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_them_free(int *pipe_fd, char *limiter, int *fd)
{
	close(pipe_fd[1]);
	if (fd[0] == -1 || fd[1] == -1)
		close (pipe_fd[0]);
	free(limiter);
}

static int	do_heredoc(int *pipe_fd, char *limiter)
{
	char	*input_buff;

	input_buff = readline("> ");
	if (input_buff)
		input_buff = ft_strfjoin(input_buff, "\n", 1);
	if (!ft_strncmp(input_buff, limiter, ft_strlen(input_buff)))
		return (free(input_buff), 1);
	ft_printf_fd(pipe_fd[1], input_buff);
	free(input_buff);
	return (0);
}

int	find_limiter(t_tokens *tokens, t_shell *shell, int *fd)
{
	t_tokens	*temp;
	char		*limiter;
	int			pipe_fd[2];
	int			i;

	(void) shell;
	temp = tokens;
	if (temp->type == LIMITER)
	{
		limiter = malloc((ft_strlen(temp->token) + 2));
		i = ft_strlen(temp->token);
		ft_strlcpy(limiter, temp->token, i + 1);
		limiter[i] = '\n';
		i++;
		limiter[i] = '\0';
		if (pipe(pipe_fd) <= -1)
			return (perror(strerror(errno)), -1);
		while (1)
			if (do_heredoc(pipe_fd, limiter) == 1)
				break ;
		if (fd[0] != -1)
			fd[0] = pipe_fd[0];
		set_them_free(pipe_fd, limiter, fd);
	}
	return (0);
}
