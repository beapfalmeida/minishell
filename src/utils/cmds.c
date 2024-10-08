#include "minishell.h"

/// @brief 
/// @param paths 
void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		i++;
	while (i--)
		free(paths[i]);
	free(paths);
}

/// @brief 
/// @param cmd 
/// @param envp 
/// @return 
char	*get_path(char	*cmd, char **envp)
{
	char	**paths;
	int		i;

	while (envp && *envp++)
		if (envp && *envp && ft_strncmp(*envp, "PATH", 4) == 0)
			break ;
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		exit(EXIT_FAILURE);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd);
		if (!paths[i])
		{
			free_paths(paths);
			return (NULL);
		}
		if (access(paths[i], R_OK) == 0)
			return (paths[i]);
		i++;
	}
	if (access(paths[i], R_OK) != 0)
	{
		// printf error
	}
	free(paths);
	return (NULL);
}

/// @brief 
/// @param token 
/// @return 
char	**put_cmds(t_tokens	*token)
{
	char		**ret;
	t_tokens	*temp;
	int			i;

	i = 0;
	temp = token;
	ret = malloc(sizeof(char *) * (count_args(token) + 1));
	if (!ret)
	{
		// TODO:clean_exit
		return (NULL);
	}
	while (temp && (temp->type == CMD || temp->type == ARG))
	{
		ret[i] = ft_strdup(temp->token);
		if (!ret[i])
		{
			free_array(ret, i);
			return (NULL);
		}
		i++;
		temp = temp->next;
	}
	ret[i] = NULL;
	return (ret);
}

// static int	do_pipe(t_tokens *tokens, t_shell *shell, int	i)
// {
// 	int	pid;
// 	int	fd[2];

// 	pid = fork();
// 	if (pipe(fd) == -1)
// 	{
// 		// TODO badpipe
// 		return (1);
// 	}
// 	if (pid < 0)
// 	{
// 		// TODO badfork
// 		return (1);
// 	}
// 	if (pid == 0)
// 	{
// 		if (i == 0)
// 		{
// 			dup2(shell->fd_in, STDIN_FILENO);
// 			close(fd[0]);
// 			dup2(fd[1], STDOUT_FILENO);
// 		}
// 		else if (i == count_args(tokens) - 1)
// 		{
// 			dup2(fd[0], STDIN_FILENO);
// 			close(fd[1]);
// 			dup2(shell->fd_out, STDOUT_FILENO);
// 		}
// 		else
// 		{
// 			dup2(fd[0], STDIN_FILENO);
// 			dup2(fd[1], STDOUT_FILENO);
// 		}
// 		if (execve(get_path(shell->cmds[i][0], shell->envp), 
// 			shell->cmds[i], shell->envp) == -1)
// 		{
// 			// TODO error command doesnt exist
// 			return (1);	
// 		}
// 	}
// }

// int	pipex(t_tokens *tokens, t_shell *shell)
// {
// 	char	**cmds;
// 	int		fd;
// 	int		i;

// 	cmds = shell->cmds;
// 	i = 0;
// 	while (*cmds)
// 	{
// 		do_pipe(tokens, shell, i);
// 		cmds++;
// 		i++;
// 	}
// }
