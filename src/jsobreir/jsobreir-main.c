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

static void	temporary_parser(char *input, t_tokens *tokens)
{
	char	**splitted;

	splitted = ft_split(input, ' ');
	if (tokens->token)
		tokens->token = ft_strdup(splitted[0]);
	if (tokens->next->token)
		tokens->next->token = ft_strdup(splitted[1]);
	if (tokens->next->next->token)
		tokens->next->next->token = ft_strdup(splitted[2]); 
	tokens->next->type = ARG;
	// shell->cmds = malloc(sizeof(char ***));
	// shell->cmds[0] = malloc (sizeof(char **));
	// shell->cmds[0][0] = ft_strdup(splitted[0]);
	// if (shell->cmds[0][1])
	// 	shell->cmds[0][1] = ft_strdup(splitted[1]);
}
/* My main Function - jsobreir- Currently Segfaulting after ctrl-D due to not exiting cleanly */
int	main(int argc, char **argv, char **envp)
{
	t_tokens	tokens;
	t_shell		shell;
	char	*input_buffer;

	(void)argc;
	(void)argv;
	shell.envp = envp;
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
		temporary_parser(input_buffer, &tokens);
		exec_cmd(&tokens, &shell);
		free(input_buffer);
		free(tokens.token);
	}
	free(input_buffer);
}
