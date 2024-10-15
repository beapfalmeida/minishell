#include "minishell.h"

int	is_file(char *file_name)
{
	struct stat	file_info;

	stat(file_name, &file_info); // get the statistics of a file or directory
	if (S_ISREG(file_info.st_mode)) // check if is a regular file
		return (1);
	if (S_ISDIR(file_info.st_mode))
		return (2);
	else
		return (0);
}