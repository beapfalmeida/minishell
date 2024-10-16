#include "minishell.h"

static int check_pwd(t_tokens *tokens, t_shell *shell)
{
    if (ft_strncmp(tokens->token, "pwd", 4))
    {
        do_error(tokens, shell, ERROR_CMD);
        return (1);
    }
    return (0);
}

/// @brief 
/// @param cwd 
/// @return 
int	ft_pwd(t_tokens *token, t_shell *shell)
{
    char    cwd[MAX_PATH_SIZE];

    if (check_pwd(token, shell))
		return (0);
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    return (1);
}
