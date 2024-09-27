#include "minishell.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*temp;
	char	*command;

	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		command = ft_strjoin(temp, cmd);
		free(temp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}
// tenho de alterar isto para receber os args se nao nao passa
char	*process_full_path(char *cmd, char **envp)
{
	char	**all_paths;
	char	**args;
	char	*path;
	int		i;
	char	*temp;

	i = 0;
	temp = cmd;
	args = ft_split(cmd, ' ');
	free(cmd);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			all_paths = ft_split(envp[i] + 5, ':');
			path = get_cmd(all_paths, *args);
			free_array(all_paths);
			return (path);
		}
		i++;
	}
	return (NULL);
}
