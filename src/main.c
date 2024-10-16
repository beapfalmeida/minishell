#include "minishell.h"

int g_signal;

static void	free_all(t_tokens *tokens, t_shell *shell, char *input_buffer)
{
	if (input_buffer)
	free(input_buffer);
	if (shell->last_path)
		free(shell->last_path);
	if (tokens)
		lstclear(&tokens);
	close(shell->original_stdin);
	close(shell->original_stdout);
}

static void	keep_parsing(t_tokens *tokens, t_shell *shell)
{
	find_expander(tokens, shell->envp);
	assign_types(&tokens);
	process_tokens(&tokens, shell); // Mudei esta funcao para antes do skip redirects para que os fds fossem colocados antes de skipar os redirects
	tokens = skip_redirects(tokens);
}

static void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = envp;
	shell->exit_code = 0;
	shell->last_path = ft_strdup(getenv("PWD"));
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
}

int	main(int argc, char **argv, char **envp)
{
	t_tokens	*tokens = NULL;
	t_shell		shell;
	char	*input_buffer;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (1)
	{
		signals();
		input_buffer = readline("minishell: ");
		if (!input_buffer || (ft_strlen(input_buffer) && !ft_strncmp(input_buffer, "exit", ft_strlen(input_buffer)))) // agora esta a dar merda - quando dou enter
		{
			printf("exit\n");
			break ;
		}
		if (!*input_buffer)
			continue ;
		if (input_buffer && *input_buffer)
			add_history(input_buffer); // Adds the input buffer to the history of cmds. Accessible by typing history in bash.
		create_tokens(&tokens, input_buffer);
		if (!tokens)
			continue ;
		keep_parsing(tokens, &shell);
		execute(tokens, &shell);
		dup2(shell.original_stdin, STDIN_FILENO);
		lstclear(&tokens);
		free(input_buffer);
	}
	free_all(tokens, &shell, input_buffer);
}
