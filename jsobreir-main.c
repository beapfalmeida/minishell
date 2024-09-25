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
}

/// @brief Function to handle signals of type SIGQUIT (ctrl-D), by calling exit_clean to exit the shell.
/// @param sig Signal code (type SIGQUIT)
void	handle_sigquit(int sig)
{
	(void)sig;
	printf("exit\n");
	// exit_clean(); TBI -------------------- Currently segfaulting
}

/// @brief The C library signal() function allows user to handle asynchronous event during the program execution
void	signals()
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

/* My main Function - jsobreir- Currently Segfaulting after ctrl-D due to not exiting cleanly */
int	main(void)
{
	t_tokens	tokens;
	char	*input_buffer;

	init_tokens(&tokens);
	while (1)
	{
		signals();
		input_buffer = readline("minishell: ");
		if (ft_strnstr(input_buffer, "\n", ft_strlen(input_buffer)))
			write(1, "minishell: ", 11);
		if (!ft_strncmp(input_buffer, "exit", ft_strlen(input_buffer)))
			break ;
		if (input_buffer && *input_buffer)
			add_history(input_buffer); // Adds the input buffer to the history of cmds. Accessible by typing history in bash.
		free(input_buffer);
	}
	free(input_buffer);
}
