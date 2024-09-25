#include "minishell.h"

void	ft_pwd(char *cwd)
{
   if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   }
	// else Error
}