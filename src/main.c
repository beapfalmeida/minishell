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

int	main(int argc, char **argv, char **envp)
{
	t_tokens	*tokens = NULL;
	t_shell		shell;
	char	*input_buffer;

	(void)argc;
	(void)argv;
	//shell.envp = envp;
	// init_tokens(tokens);
	while (1)
	{
		signals();
		shell.last_path = ft_strdup(getenv("PWD"));
		input_buffer = readline("minishell: ");
		if (ft_strnstr(input_buffer, "\n", ft_strlen(input_buffer)))
			write(1, "minishell: ", 11);
		if (!ft_strncmp(input_buffer, "exit", ft_strlen(input_buffer)))
			break ;
		if (input_buffer && *input_buffer)
			add_history(input_buffer); // Adds the input buffer to the history of cmds. Accessible by typing history in bash.
		create_tokens(&tokens, input_buffer);
		//find_expander(tokens, envp);
		process_tokens(&tokens, &shell, envp);
		exec_cmd(tokens, &shell);
		lstclear(&tokens);
		//TODO: dar free a shell
	}
	free(input_buffer);
}
