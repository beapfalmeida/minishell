#include "minishell.h"

/// @brief 
/// @param cwd 
/// @return 
int	ft_pwd()
{
    char    cwd[MAX_PATH_SIZE];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
	// else Error
    return (0);
}