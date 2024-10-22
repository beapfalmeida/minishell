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
	char	*joined;
	char	*temp;

	while (envp && *envp++)
		if (envp && *envp && ft_strncmp(*envp, "PATH", 4) == 0)
			break ;
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		exit(EXIT_FAILURE);
	i = 0;
	while (paths[i])
	{
		joined = ft_strjoin(paths[i], "/");
		temp = joined;
		joined = ft_strjoin(joined, cmd);
		free(temp);
		if (!joined)
		{
			free_paths(paths);
			return (NULL);
		}
		if (access(joined, R_OK) == 0)
		{
			free_paths(paths);
			return (joined);
		}
		i++;
		free(joined);
	}
	free_paths(paths);
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
		return (NULL);
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

