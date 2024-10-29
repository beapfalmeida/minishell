#include "minishell.h"

int g_signal;

void	child_cleanup(t_tokens *tokens, t_shell *shell)
{
	if (shell->last_path)
		free(shell->last_path);
	if (shell->envp)
		free_paths(shell->envp);
	if (tokens)
		lstclear(&tokens);
	if (shell->original_stdin)
		close(shell->original_stdin);
	if (shell->original_stdout)
		close(shell->original_stdout);
	if (shell->fd_in)
		close(shell->fd_in);
	if (shell->fd_out)
		close(shell->fd_out);
}

static void	free_all(t_tokens *tokens, t_shell *shell, char *input_buffer)
{
	if (shell->last_path)
		free(shell->last_path);
	if (shell->envp)
		free_paths(shell->envp);
	if (tokens)
		lstclear(&tokens);
	if (shell->original_stdin)
		close(shell->original_stdin);
	if (shell->original_stdout)
		close(shell->original_stdout);
	if (input_buffer)
		free(input_buffer);
}

static t_tokens	*keep_parsing(t_tokens *tokens, t_shell *shell)
{
	t_tokens *temp;
	t_tokens *t;
	handle_quotes(tokens, shell);
	// if (*tokens->token == '\0')
	// 	return (NULL);
	assign_types(&tokens);
	if (has_sintax_error(tokens, shell))
		return (NULL);
	if (process_tokens(&tokens, shell)) // Mudei esta funcao para antes do skip redirects para que os fds fossem colocados antes de skipar os redirects
		return (NULL);
	temp = tokens;
	tokens = skip_redirects(tokens);
	while (temp)
	{
		t = temp->next;
		free(temp);
		temp = t;
	}
	return (tokens);
}

static void	init_shell(t_shell *shell, char **envp)
{
	char	**envp_array;
	int		i;

	envp_array = malloc((arr_len(envp) + 1) * sizeof(char *));
	i = 0;
	while (envp[i])
	{
		envp_array[i] = ft_strdup(envp[i]);
		if (!envp_array[i])
			free_array(&envp_array[i], i);
		i++;
	}
	envp_array[i] = NULL;
	shell->envp = envp_array;
	shell->exit_code = "0";
	shell->last_path = ft_strdup(getenv("PWD"));
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
	shell->interrupt_exec = false;
}

int	main(int argc, char **argv, char **envp)
{
	t_tokens	*tokens = NULL;
	t_shell		shell;
	char		*input_buffer;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (1)
	{
		signals();
		input_buffer = readline("minishell: ");
		if (g_signal == SIGINT)
		{
			shell.exit_code = "130";
			g_signal = 0;
		}
		if (!input_buffer || (ft_strlen(input_buffer) && !ft_strncmp(input_buffer, "exit", 4)))
		{
			printf("exit\n");
			break ;
		}
		if (!*input_buffer)
			continue ;
		if (input_buffer && *input_buffer)
			add_history(input_buffer);
		create_tokens(&tokens, input_buffer);
		if (!tokens)
			continue ;
		tokens = keep_parsing(tokens, &shell);
		if (shell.interrupt_exec == true)
		{
			shell.interrupt_exec = false;
			free_all(tokens, &shell, input_buffer);
			continue ;
		}
		if (tokens)	// Voltei a colocar assim pois se for if (!tokens): continue,  ele nao faz o dup2 de volta para o stdin_original e le do fd do heredoc na proxima readline
			execute(tokens, &shell);
		dup2(shell.original_stdin, STDIN_FILENO);
		dup2(shell.original_stdin, STDOUT_FILENO);
		lstclear(&tokens);
		free(input_buffer);
	}
	free_all(tokens, &shell, input_buffer);
	exit(ft_atoi(shell.exit_code));
}
