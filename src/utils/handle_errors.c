#include "minishell.h"

void	badfork(int pid, char *strerr)
{
	if (pid == -1)
	{
		perror(strerr);
		exit(1); // implement error code
	}
}

void	badpath(char *path, char *cmd)
{
	if (!path)
	{
		printf("Command not found: %s\n", cmd);
		exit(1); // implement error code
	}
}

void	badopen(int fd, char *file)
{
	if (fd == -1)
	{
		printf("No such file or directory: %s\n", file);
		exit(1); // implement error code
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
