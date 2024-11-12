#include "minishell.h"

/// @brief Function to handle signals of type SIGINT (ctrl-C),
/// that displays a prompt on the shell.
/// @param sig Signal code (type SIGINT)
void	handle_sigint(int sig)
{
	ft_printf_fd(STDERR_FILENO, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = sig;
}

/// @brief The C library signal() function allows 
///user to handle asynchronous event during the program execution
void	signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signore(int sig)
{
	ft_printf_fd(STDOUT_FILENO, "\n");
	g_signal = sig;
}
