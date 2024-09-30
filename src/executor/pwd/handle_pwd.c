#include "minishell.h"

/// @brief 
/// @param cwd 
/// @return 
int	ft_pwd(void)
{
    char    cwd[MAX_PATH_SIZE];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        // Handle Error
        return (1);
    }
    return (0);
}
