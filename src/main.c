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
	shell.envp = envp;
	shell.last_path = ft_strdup(getenv("PWD"));
	shell.original_stdin = 6;
	shell.original_stdout = 6;
	dup2(STDIN_FILENO, shell.original_stdin);
	// dup2(STDOUT_FILENO, shell.original_stdout);
	while (1)
	{
		signals();
		input_buffer = readline("minishell: ");
		if (!ft_strncmp(input_buffer, "exit", ft_strlen(input_buffer)))
			break ;
		if (input_buffer && *input_buffer)
			add_history(input_buffer); // Adds the input buffer to the history of cmds. Accessible by typing history in bash.
		create_tokens(&tokens, input_buffer);
		process_tokens(&tokens, &shell); // Mudei esta funcao para antes do skip redirects para que os fds fossem colocados antes de skipar os redirects
		tokens = skip_redirects(tokens);
		tokens = handle_quotes(tokens, &shell);
		// find_expander(tokens, shell.envp);
		if (shell.fd_in != -1 && shell.fd_out != -1)
			execute(tokens, &shell);
		// else printa erro
		dup2(shell.original_stdin, STDIN_FILENO);
		lstclear(&tokens);
	}
	if (input_buffer)
		free(input_buffer);
	if (shell.last_path)
		free(shell.last_path);
	if (tokens)
		lstclear(&tokens);
	close(shell.original_stdin);
	close(shell.original_stdout);
}
