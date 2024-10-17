#include "minishell.h"

/// @brief Function to handle signals of type SIGINT (ctrl-C), that displays a prompt on the shell.
/// @param sig Signal code (type SIGINT)
void	handle_sigint(int sig)
{
    (void)sig;
    write(2, "\n", 1);
    rl_replace_line("", 0);// Replaces line buffer with new string.
    rl_on_new_line();
    rl_redisplay();
	g_signal = SIGINT;
}

/// @brief The C library signal() function allows user to handle asynchronous event during the program execution
void	signals(t_shell *shell)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (g_signal == SIGINT)
		shell->exit_code = 130;
}
