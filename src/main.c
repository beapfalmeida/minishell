#include "minishell.h"

char	*get_error(t_error i)
{
	char	*str[17];

	str[0] = "%s: Command not found\n";
	str[1] = "bash: %s: %s: No such file or directory\n";
	str[2] = "bash: %s: too many arguments\n";
	str[3] = "bash: %s: Makefile: Not a directory\n";
	return (str[i]);
}

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

int	main(int argc, char **argv, char **envp)
{
	t_tokens	*tokens = NULL;
	t_shell		shell;
	char	*input_buffer;

	(void)argc;
	(void)argv;
	shell.envp = envp;
	shell.last_path = ft_strdup(getenv("PWD"));
	shell.original_stdin = dup(STDIN_FILENO);
	shell.original_stdout = dup(STDOUT_FILENO);
	while (1)
	{
		signals();
		input_buffer = readline("minishell: ");
		if (!*input_buffer)
			continue ;
		if (!ft_strncmp(input_buffer, "exit", ft_strlen(input_buffer)))
		{
			printf("exit\n");
			break ;
		}
		if (input_buffer && *input_buffer)
			add_history(input_buffer); // Adds the input buffer to the history of cmds. Accessible by typing history in bash.
		create_tokens(&tokens, input_buffer);
		if (!tokens)
			continue ;
		process_tokens(&tokens, &shell); // Mudei esta funcao para antes do skip redirects para que os fds fossem colocados antes de skipar os redirects
		tokens = skip_redirects(tokens);
		find_expander(tokens, shell.envp);
		execute(tokens, &shell);
		dup2(shell.original_stdin, STDIN_FILENO);
		lstclear(&tokens);
	}
	free_all(tokens, &shell, input_buffer);
}
