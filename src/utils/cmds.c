/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsobreir <jsobreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:46:01 by jsobreir          #+#    #+#             */
/*   Updated: 2024/11/20 15:46:03 by jsobreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Free an array.
/// @param paths Array to free.
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

/// @brief Finds the string in $PATH and splits it by the :, 
/// so that each path can then be searched for cmds.
/// @param envp Pointer to an array of environment variables.
/// @return 
static char	**get_patharr(char **envp)
{
	char	**paths;
	int		flag;

	flag = 0;
	paths = NULL;
	while (envp && *envp++)
	{
		if (envp && *envp && ft_strncmp(*envp, "PATH", 4) == 0)
		{
			flag = 1;
			break ;
		}
	}
	if (flag == 1)
		paths = ft_split(*envp + 5, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*get_path(char	*cmd, char **env)
{
	int		i;
	char	*joined;
	char	**envp;
	char	**paths;

	envp = env;
	paths = get_patharr(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		joined = ft_strjoin(paths[i], "/");
		joined = ft_strfjoin(joined, cmd, 1);
		if (!joined)
			return (free_paths(paths), NULL);
		if (access(joined, R_OK) == 0)
			return (free_paths(paths), joined);
		i++;
		free(joined);
	}
	free_paths(paths);
	if (*cmd == '/')
		return (cmd);
	return (NULL);
}

/// @brief Creates an array of commands.
/// @param token Pointer to list of tokens.
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
	while (temp && (temp->type == CMD || temp->type == ARG
			|| temp->type == DIR_FILE))
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
