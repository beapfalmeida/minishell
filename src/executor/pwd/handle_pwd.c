#include "minishell.h"

static int check_pwd(t_tokens *tokens)
{
    if (ft_strncmp(tokens->token, "pwd", 4))
    {
        printf(get_error(ERROR_CMD), tokens->token);
        return (1);
    }
    return (0);
}

/// @brief 
/// @param cwd 
/// @return 
int	ft_pwd(t_tokens *token)
{
    char    cwd[MAX_PATH_SIZE];

    if (check_pwd(token))
		return (0);
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    return (1);
}
