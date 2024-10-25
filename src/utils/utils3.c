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

int	has_sintax_error(t_tokens *tokens, t_shell *shell)
{
	t_tokens *temp;
	temp = tokens;
	while (temp)
	{
		if (temp->type == ERROR_SYNTAX)
			return(do_error(tokens, shell, ERROR_SYNTAX), 1);
		if (temp->type == ERROR_PIPE)
		return(do_error(tokens, shell, ERROR_SYNTAX), 1);
		temp = temp->next;
	}
	return (0);
}

char	*ft_strfjoin(char *s1, char *s2, int _to_free)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	if (_to_free == 1 || _to_free == 3)
		free(s1);
	if (_to_free == 2 || _to_free == 3)
		free(s2);
	return (new_str);
}
