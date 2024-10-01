#include "minishell.h"

static int check_pwd(t_tokens *tokens)
{
    if (ft_strncmp(tokens->token, "pwd", 4))
    {
        // TODO return invalid command
        return (1);
    }
    else if (tokens->next && tokens->next->type == ARG)
    {
        // TODO return too many commands
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

    check_pwd(token);
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
