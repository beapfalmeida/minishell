#include "minishell.h"

int	is_file(char *file_name)
{
	struct stat	file_info;
	int			res;

	res = stat(file_name, &file_info);
	if (res == -1)
		return (0);
	if (S_ISREG(file_info.st_mode))
	{
		if (file_info.st_mode & S_IXUSR)
			return (1);
		else
			return (4);
	}
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
	t_tokens	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->type == ERROR_SYNTAX)
			return (do_error(0, temp, shell, ERROR_SYNTAX), 1);
		if (temp->type == ERROR_PIPE)
			return (do_error(0, temp, shell, ERROR_SYNTAX), 1);
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

long	getexitcode(t_tokens *tokens, char *number)
{
	long long	ret;
	int			i;
	int			overflow;

	overflow = 0;
	(void)tokens;
	i = 0;
	ft_printf_fd(STDOUT_FILENO, "exit\n");
	if (number[0] == '+')
		i++;
	while (number[0] == '-' && number[i] == '-')
		i++;
	while (number[i])
	{
		if (error_exit1(number, i))
			return (2);
		i++;
	}
	ret = ft_atoll(number, &overflow);
	if (error_exit2(overflow, ret, number))
		return (2);
	if (!(0 <= ret && ret <= 255))
		ret %= 256;
	return ((long)ret);
}
