#include "minishell.h"

int	is_file(char *file_name)
{
	struct stat	file_info;
	int res;

	res = stat(file_name, &file_info); // get the statistics of a file or directory
	if (res == -1) // if theres no such file or dir
		return (0);
	if (S_ISREG(file_info.st_mode)) // check if is a regular file
		return (1);
	if (S_ISDIR(file_info.st_mode))
		return (2);
	else
		return (3);
}

int	has_char(char *token, char c)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == c)
			return (1);
		i++;
	}
	return (0);
}