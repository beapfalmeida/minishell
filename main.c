#include "minishell.h"

void	parse(char *str)
{
	(void)str;
}

int	main()
{
	char *str;
	write(1, "minishell: ", 11);
	while (1)
	{
		//descobrir como se usa isto :)
		str = readline("minishell: ");
		if (ft_strnstr(str, "\n", ft_strlen(str)))
			write(1, "minishell: ", 11);
		if (!ft_strncmp(str, "exit", ft_strlen(str)))
			break ;
		parse(str);
		free(str);
	}
	free(str);
}